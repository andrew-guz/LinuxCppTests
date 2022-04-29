#include "BuildUIHelper.h"

#include <cassert>

#include "WtGlobal.h"

using namespace Wt;

WWidget* BuildUIHelper::createWidget(WGridLayout* gridLayout, int row, Property& property)
{
    assert(property.editorInfo()._editorType != PropertyAdditions::EditorType::Unknown &&
           property.editorInfo()._additionalInformation != nullptr);
    if (property.editorInfo()._editorType != PropertyAdditions::EditorType::Unknown &&
        property.editorInfo()._additionalInformation != nullptr)
    {
        gridLayout->addWidget(std::make_unique<WText>(property.displayName()), row, 0);
        switch (property.editorInfo()._editorType)
        {
        case PropertyAdditions::EditorType::LineEdit:
            return gridLayout->addWidget(std::make_unique<WLineEdit>(property.data().toString()), row, 1);
        case PropertyAdditions::EditorType::PasswordLineEdit:
            {
                auto editor = gridLayout->addWidget(std::make_unique<WLineEdit>(property.data().toString()), row, 1);
                editor->setEchoMode(EchoMode::Password);
                return editor;
            }
        case PropertyAdditions::EditorType::Integer:
            {
                auto integerLimits = std::dynamic_pointer_cast<PropertyAdditions::IntegerLimits>(property.editorInfo()._additionalInformation);
                auto editor = gridLayout->addWidget(std::make_unique<WSpinBox>(), row, 1);
                editor->setMinimum(integerLimits->_min);
                editor->setMaximum(integerLimits->_max);
                editor->setValue(property.data().toInt());
                return editor;
            }
        default:
            assert(false);
            break;
        }
    }

    return nullptr;
}
