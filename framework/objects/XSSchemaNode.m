//
//  XmlAccess.m
//  xsd2cocoa
//
//  Created by Stefan Winter on 5/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "XSSchemaNode.h"
#import "XSDschema.h"
#import "XMLUtils.h"
#import "XSDAnnotation.h"

@interface XSSchemaNode ()

@property (nonatomic, strong) NSXMLElement* node;
@property (nonatomic, weak) XSDschema* schema;

@end

@implementation XSSchemaNode {
    NSMutableArray *_annotations;
}

- (instancetype) initWithNode:(NSXMLElement*)node schema:(XSDschema*)schema {
    self = [self init];
    if(self) {
        _node = node;
        
        if(!schema && [self isKindOfClass:[XSDschema class]]) {
            _schema = (XSDschema*)self;
        }
        else {
            _schema = schema;
        }
    }
    return self;
}

- (NSArray *)annotations {
    if(!_annotations) {
        NSArray * elems = [XMLUtils node:self.node childrenWithName:@"annotation"];
        _annotations = [NSMutableArray arrayWithCapacity:elems.count];
        
        for (NSXMLElement *elem in elems) {
            XSDAnnotation *annotation = [[XSDAnnotation alloc] initWithNode:elem schema:self.schema];
            if(annotation) {
                [_annotations addObject:annotation];
            }
        }
    }
    return _annotations;
}

- (BOOL)hasAnnotations {
    return (self.annotations.count != 0);
}

- (NSString*)comment {
    NSMutableString *allComments = [NSMutableString string];
    for (XSDAnnotation *ann in self.annotations) {
        NSString *annComment = ann.comment;
        if(annComment.length) {
            if(allComments.length) {
                [allComments appendString:@"\n"];
            }
            [allComments appendString:annComment];
        }
    }
    return allComments;
}

@end
