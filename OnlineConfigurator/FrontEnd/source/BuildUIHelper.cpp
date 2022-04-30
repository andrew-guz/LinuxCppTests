#include "BuildUIHelper.h"

#include <cassert>

#include "WtGlobal.h"
#include "UrlBuilder.h"
#include "VariantSerializer.h"

using namespace Wt;

WWidget* BuildUIHelper::createWidget(WGridLayout* gridLayout, int row, const Property& property, const Uuid& entityId, const std::string& requestName, HttpClientUser* httpCLientUser)
{
    assert(property.editorInfo()._editorType != PropertyAdditions::EditorType::Unknown);
    if (property.editorInfo()._editorType == PropertyAdditions::EditorType::Unknown)
        return nullptr;

    auto displayName = property.displayName();
    if (displayName.compare(displayName.size() - 1, 1, ":") != 0)
        displayName.append(":");
    gridLayout->addWidget(std::make_unique<WText>(displayName), row, 0);
    switch (property.editorInfo()._editorType)
    {
    case PropertyAdditions::EditorType::LineEdit:
        {
            auto editor = gridLayout->addWidget(std::make_unique<WLineEdit>(property.data().toString()), row, 1);
            editor->changed().connect([editor, property, entityId, requestName, httpCLientUser]()
            {
                auto url = UrlBuilder::instance()->propertyUrl(entityId, property.name());
                Variant data = editor->text().toUTF8();
                httpCLientUser->put(requestName, url, VariantSerializer::toJson(data).dump(4));
            });
            return editor;
        }
    case PropertyAdditions::EditorType::PasswordLineEdit:
        {
            auto editor = gridLayout->addWidget(std::make_unique<WLineEdit>(property.data().toString()), row, 1);
            editor->setEchoMode(EchoMode::Password);
            editor->changed().connect([editor, property, entityId, requestName, httpCLientUser]()
            {
                auto url = UrlBuilder::instance()->propertyUrl(entityId, property.name());
                Variant data = editor->text().toUTF8();
                httpCLientUser->put(requestName, url, VariantSerializer::toJson(data).dump(4));
            });
            return editor;
        }
    case PropertyAdditions::EditorType::Integer:
        {
            assert(property.editorInfo()._additionalInformation != nullptr);
            if (property.editorInfo()._additionalInformation == nullptr)
                return nullptr;
            auto integerLimits = std::dynamic_pointer_cast<PropertyAdditions::IntegerLimits>(property.editorInfo()._additionalInformation);
            auto editor = gridLayout->addWidget(std::make_unique<WSpinBox>(), row, 1);
            editor->setMinimum(integerLimits->_min);
            editor->setMaximum(integerLimits->_max);
            editor->setValue(property.data().toInt());
            editor->changed().connect([editor, property, entityId, requestName, httpCLientUser]()
            {
                auto url = UrlBuilder::instance()->propertyUrl(entityId, property.name());
                Variant data = editor->value();
                httpCLientUser->put(requestName, url, VariantSerializer::toJson(data).dump(4));
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
        auto widget = createWidget(gridLayout, row, property, entity->id(), requestName, httpCLientUser);
        assert(widget);
        if (widget)
            result.emplace(propertyName, widget);
    }
    return result;
}
