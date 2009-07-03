#ifndef SGF_PROPERTY_H
#define SGF_PROPERTY_H

enum PropertyType {
    MoveProperty    ,
    SetupProperty   ,
    NodeAnnotationProperty,
    MoveAnnotationProperty,
    MarkupProperty,
    RootProperty,
    GameInfoProperty,
    TimingProperty,
    MiscProperty
};

class SgfProperty {
    private:
        PropertyType type;
    public:
        SgfProperty();
        ~SgfProperty();
        PropertyType getType();
        void setType(PropertyType type);
};

#endif // SGF_PROPERTY_H
