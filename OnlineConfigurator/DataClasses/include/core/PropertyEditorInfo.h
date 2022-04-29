#ifndef _PROPERTYEDITORINFO_H_
#define _PROPERTYEDITORINFO_H_

#include <memory>

namespace PropertyAdditions
{
    enum class EditorType
    {
        Unknown,
        LineEdit,
        PasswordLineEdit,
        Integer
    };

    enum class AdditionalInformationType
    {
        None,
        IntLimits
    };

    class AdditionalInformation
    {
    public:
        AdditionalInformation(AdditionalInformationType type);

        virtual ~AdditionalInformation() = default;

        AdditionalInformationType type() const;

    private:
        AdditionalInformationType _type;
    };

    class IntegerLimits final : public AdditionalInformation
    {
    public:
        IntegerLimits(int min, int max);

        virtual ~IntegerLimits() = default;

        int _min = 0;
        int _max = 100;
    };

    class PropertyEditorInfo final
    {
    public:
        EditorType                              _editorType = EditorType::Unknown;
        std::shared_ptr<AdditionalInformation>  _additionalInformation = nullptr;
    };

};

#endif //_PROPERTYEDITORINFO_H_
