//
//  XSDschema.h
//  xsd2cocoa
//
//  Created by Stefan Winter on 5/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import "XSSchemaNode.h"

@protocol XSType;
@protocol FileFormatter;
@class XSDcomplexType;

typedef NS_OPTIONS(NSUInteger, XSDschemaGeneratorOptions) {
    XSDschemaGeneratorOptionSourceCode = 1 << 0,
    XSDschemaGeneratorOptionSourceCodeWithSubfolders = 1 << 1,
    XSDschemaGeneratorOptionLowercaseProperties = 1 << 2,
    XSDschemaGeneratorOptionIndentWithTabs = 1 << 3,
    XSDschemaGeneratorOptionValidateXsdSchema = 1 << 4
};

@interface XSDschema : XSSchemaNode

@property (readonly, nonatomic) NSString* schemaId;
@property (readonly, nonatomic) NSURL* schemaUrl;
@property (readonly, nonatomic) NSString* targetNamespace;
@property (readonly, nonatomic) NSArray* allNamespaces;
@property (readonly, nonatomic) NSArray* complexTypes;
@property (readonly, nonatomic) NSArray* includedSchemas;//included and imported both. except for namespacing, we dont care
@property (readonly, nonatomic) NSArray* simpleTypes;
@property (readonly, nonatomic) NSString *xmlSchemaNamespace;
@property (readonly, nonatomic) XSDschemaGeneratorOptions options;
- (NSString*)nameSpacedSchemaNodeNameForNodeName:(NSString*)nodeName;

@property (readonly, weak, nonatomic) XSDschema* parentSchema;

//create the scheme, loading all types and includes
// (XSDschemaGeneratorOptions) - the options that the user selected and the type of code to write
- (instancetype) initWithUrl: (NSURL*) schemaUrl targetNamespacePrefix: (NSString*) prefix options: (XSDschemaGeneratorOptions)options error: (NSError**) error;

//element may add local types (Complex or simple)
- (void) addType: (id<XSType>)type;

- (BOOL) loadTemplate: (NSURL*) templateUrl error: (NSError**) error;
- (id<XSType>) typeForName: (NSString*) qname; //this will only return proper type info when called during generation
- (NSString*)classPrefixForType:(id<XSType>)type;
- (NSString*) variableNameFromName:(NSString*)vName multiple:(BOOL)multiple;

#pragma mark -

//generate code using loaded template
- (BOOL) generateInto: (NSURL*) destinationFolder
                error: (NSError**) error;

@end
