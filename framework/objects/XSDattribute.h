#import "XSSchemaNode.h"


typedef NS_ENUM(NSUInteger, XSDattributeUse) {
    XSDattributeUseOptional,
    XSDattributeUseProhibited,
    XSDattributeUseRequired,
};

@interface XSDattribute : XSSchemaNode

@property (readonly, nonatomic) NSString* name;
@property (readonly, nonatomic) NSString* simpleType;
@property (readonly, nonatomic) NSString* type;
@property (readonly, nonatomic) XSDattributeUse use;
@property (readonly, nonatomic) NSString* defaultValue;
@property (readonly, nonatomic) NSString* fixed;
@property (readonly, nonatomic) NSString* form;

@property (readonly, nonatomic) NSString* readCodeForAttribute;
@property (readonly, nonatomic) NSString* writeCodeForAttribute;

- (NSString*) variableName; //name in generated code
- (BOOL) hasEnumeration;
- (BOOL) isUseOptional;
- (BOOL) isUseRequired;

@end
