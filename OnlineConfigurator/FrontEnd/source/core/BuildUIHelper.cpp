#include "BuildUIHelper.h"

#include <cassert>

#include "WtGlobal.h"
#include "UrlBuilder.h"
#include "VariantSerializer.h"

using namespace Wt;

WWidget* BuildUIHelper::createTextWidget(Wt::WGridLayout* gridLayout, const Property& property, const GridPosition& gridPosition)
{
    auto displayName = property.displayName();
    if (displayName.compare(displayName.size() - 1, 1, ":") != 0)
        displayName.append(":");
    return gridLayout->addWidget(std::make_unique<WText>(displayName), gridPosition._row, gridPosition._column, gridPosition._rowSpan, gridPosition._columnSpan);
}

WWidget* BuildUIHelper::createWidget(WGridLayout* gridLayout, const Property& property, const GridPosition& gridPosition, const UpgradeHelpInfo& upgradeHelpInfo)
{
    assert(property.editorInfo()._editorType != PropertyAdditions::EditorType::Unknown);
    if (property.editorInfo()._editorType == PropertyAdditions::EditorType::Unknown)
        return nullptr;

    switch (property.editorInfo()._editorType)
    {
    case PropertyAdditions::EditorType::LineEdit:
        {
            auto editor = gridLayout->addWidget(std::make_unique<WLineEdit>(property.data().toString()), gridPosition._row, gridPosition._column, gridPosition._rowSpan, gridPosition._columnSpan);
            editor->changed().connect([editor, propertyName = property.name(), upgradeHelpInfo]()
            {
                auto url = UrlBuilder::instance()->propertyUrl(upgradeHelpInfo._entityId, propertyName);
                Variant data = editor->text().toUTF8();
                upgradeHelpInfo._httpCLientUser->put(upgradeHelpInfo._requestName, url, VariantSerializer::toJson(data).dump(4));
            });
            return editor;
        }
    case PropertyAdditions::EditorType::PasswordLineEdit:
        {
            auto editor = gridLayout->addWidget(std::make_unique<WLineEdit>(property.data().toString()), gridPosition._row, gridPosition._column, gridPosition._rowSpan, gridPosition._columnSpan);
            editor->setEchoMode(EchoMode::Password);
            editor->changed().connect([editor, propertyName = property.name(), upgradeHelpInfo]()
            {
                auto url = UrlBuilder::instance()->propertyUrl(upgradeHelpInfo._entityId, propertyName);
                Variant data = editor->text().toUTF8();
                upgradeHelpInfo._httpCLientUser->put(upgradeHelpInfo._requestName, url, VariantSerializer::toJson(data).dump(4));
            });
            return editor;
        }
    case PropertyAdditions::EditorType::Integer:
        {
            assert(property.editorInfo()._additionalInformation != nullptr);
            if (property.editorInfo()._additionalInformation == nullptr)
                return nullptr;
            auto integerLimits = std::dynamic_pointer_cast<PropertyAdditions::IntegerLimits>(property.editorInfo()._additionalInformation);
            auto editor = gridLayout->addWidget(std::make_unique<WSpinBox>(), gridPosition._row, gridPosition._column, gridPosition._rowSpan, gridPosition._columnSpan);
            editor->setMinimum(integerLimits->_min);
            editor->setMaximum(integerLimits->_max);
            editor->setValue(property.data().toInt());
            editor->changed().connect([editor, propertyName = property.name(), upgradeHelpInfo]()
            {
                auto url = UrlBuilder::instance()->propertyUrl(upgradeHelpInfo._entityId, propertyName);
                Variant data = editor->value();
                upgradeHelpInfo._httpCLientUser->put(upgradeHelpInfo._requestName, url, VariantSerializer::toJson(data).dump(4));
            });
            return editor;
        }
    default:
        assert(false);
        break;
    }

    return nullptr;
}

std::map<std::string, Wt::WWidget*> BuildUIHelper::fillGridLayout(Wt::WGridLayout* gridLayout, const IEntity* entity, const std::string& requestName, HttpClientUser* httpCLientUser)
{
    assert(gridLayout &&
           entity &&
           requestName.size() &&
           httpCLientUser);
    std::map<std::string, Wt::WWidget*> result;
    auto id = entity->id();
    auto propertyNames = entity->listPropertyNames();
    for (int row = 0; row < propertyNames.size(); ++row)
    {
        const auto& propertyName = propertyNames[row];
        const auto& property = entity->property(propertyName);
        auto text = createTextWidget(gridLayout, property, { row, 0, 1, 1 });
        auto widget = createWidget(gridLayout, property, { row, 1, 1, 1 }, { entity->id(), requestName, httpCLientUser });
        assert(widget);
        if (widget)
            result.emplace(propertyName, widget);
    }
    return result;
}
