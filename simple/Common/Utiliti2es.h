//
//  Utilities.h
//  MKDropdownMenuExample
//
//  Created by Max Konovalov on 17/03/16.
//  Copyright © 2016 Max Konovalov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SCLAlertView.h"
#import "UNIRest/UNIRest.h"
//SCLAlertView *alert;
//enum definition
typedef NS_ENUM(NSInteger, SectionDefinition) {//for two cards
    LeftSecion = 0,
    RightSection,
    Center
};
typedef NS_ENUM(NSInteger, ThemDefinition) {//for Theme distinguish
    StandardTheme = 0,
    ProTheme
};
typedef NS_ENUM(NSInteger, DropdownComponents) {//drop down
    DropdownComponentShape = 0,
    DropdownComponentColor,
    DropdownComponentsCount
};
typedef NS_ENUM(NSInteger, MXCardDestination) {//tinder card
    MXCardDestinationCenter = 0,
    MXCardDestinationLeft,
    MXCardDestinationRight,
    MXCardDestinationUp
};

static NSString *BaseURI = @"http://192.168.2.155:3000/";
//static NSString *BaseURI = @"https://korteapi.herokuapp.com/";
static UIView* copyView(UIView * view) {
    NSData *archivedData = [NSKeyedArchiver archivedDataWithRootObject: view];
    UIView* copy = [NSKeyedUnarchiver unarchiveObjectWithData: archivedData];
    return copy;
}
//delay(0.15, ^{[dropdownMenu closeAllComponentsAnimated:YES];});
static inline void delay(NSTimeInterval delay, dispatch_block_t block) {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), dispatch_get_main_queue(), block);
}
//self.view.backgroundColor = UIColorWithHexString(@"#166BB5");
static UIColor * UIColorWithHexString(NSString *hex) {
    unsigned int rgb = 0;
    [[NSScanner scannerWithString:
      [[hex uppercaseString] stringByTrimmingCharactersInSet:
       [[NSCharacterSet characterSetWithCharactersInString:@"0123456789ABCDEF"] invertedSet]]]
     scanHexInt:&rgb];
    return [UIColor colorWithRed:((CGFloat)((rgb & 0xFF0000) >> 16)) / 255.0
                           green:((CGFloat)((rgb & 0xFF00) >> 8)) / 255.0
                            blue:((CGFloat)(rgb & 0xFF)) / 255.0
                           alpha:1.0];
}

//standard color
static UIColor * StandardColor(){
    return UIColorWithHexString(@"ff9933");
}

//bottom style color
static UIColor * BottomColor(){
    return UIColorWithHexString(@"EF7D68");
}

static UIImage * croppIngimageByImageName(UIImage * imageToCrop, CGRect rect)
{
    //CGRect CropRect = CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height+15);
    
    CGImageRef imageRef = CGImageCreateWithImageInRect([imageToCrop CGImage], rect);
    UIImage *cropped = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    
    return cropped;
}
static UIImage* imageWithBorderFromImage(UIImage* source)
{
    CGSize size = [source size];
    UIGraphicsBeginImageContext(size);
    CGRect rect = CGRectMake(0, 0, size.width, size.height);
    [source drawInRect:rect blendMode:kCGBlendModeNormal alpha:1.0];
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetRGBStrokeColor(context, 1.0, 0.5, 1.0, 1.0);
    CGContextStrokeRect(context, rect);
    UIImage *testImg =  UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return testImg;
}
static UIImage * makeRoundedImage(UIImage * image,
 float radius)
{
    CALayer *imageLayer = [CALayer layer];
    imageLayer.frame = CGRectMake(0, 0, image.size.width, image.size.height);
    
    imageLayer.contents = (id) image.CGImage;
    
    imageLayer.masksToBounds = YES;
    imageLayer.cornerRadius = radius;
   
    
    UIGraphicsBeginImageContext(image.size);
    [imageLayer renderInContext:UIGraphicsGetCurrentContext()];
    UIImage *roundedImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return roundedImage;
}

static NSAttributedString* attributedString(NSString * contentString, UIColor * color, CGFloat fontSize){
    NSString *textContent = contentString;
    UIColor *textColor = color?color:StandardColor();
    NSAttributedString *attributedString =
    [[NSAttributedString alloc]
     initWithString:textContent
     attributes:
     @{
       NSForegroundColorAttributeName:textColor,
       NSKernAttributeName : @(fontSize)
       }];
    return attributedString;
    
}
static NSString* jsonStringify(NSDictionary *arr){
    NSError *error;
    NSData *jsonData2 = [NSJSONSerialization dataWithJSONObject:arr options:NSJSONWritingPrettyPrinted error:&error];
    NSString *jsonString = [[NSString alloc] initWithData:jsonData2 encoding:NSUTF8StringEncoding];
    return jsonString;
}
static NSData* jsonParse(NSString *stringJson){
    NSData *data = [stringJson dataUsingEncoding:NSUTF8StringEncoding];
    id json = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
    return json;
}
static UIImage* imageWithImage(UIImage* image, CGSize size) {
    UIGraphicsBeginImageContext(size);
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *destImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return destImage;
}
static void alertCustom(SCLAlertViewStyle alertStyle, UIViewController *self,NSString *subtitle){
    SCLAlertView *alert = [[SCLAlertView alloc] init];
    switch (alertStyle) {
        case SCLAlertViewStyleSuccess:
            [alert showSuccess:self title:@"Hello World" subTitle:@"This is a more descriptive text." closeButtonTitle:@"Done" duration:0.0f];
            break;
        case SCLAlertViewStyleWaiting:
            [alert showWaiting:self title:@"Waiting..." subTitle:@"Please wait a moment." closeButtonTitle:nil duration:0.0f];
            break;
        case SCLAlertViewStyleError:
            [alert showError:self title:@"Error Notification!" subTitle:subtitle closeButtonTitle:@"OK" duration:0.0f]; // Error
            break;
        default:
            [alert hideView];
            break;
    }
    // Get started
    
    
    
    
    // Alternative alert types
    
    //    [alert showNotice:self title:@"Hello Notice" subTitle:@"This is a more descriptive notice text." closeButtonTitle:@"Done" duration:0.0f]; // Notice
    //    [alert showWarning:self title:@"Hello Warning" subTitle:@"This is a more descriptive warning text." closeButtonTitle:@"Done" duration:0.0f]; // Warning
    //    [alert showInfo:self title:@"Hello Info" subTitle:@"This is a more descriptive info text." closeButtonTitle:@"Done" duration:0.0f]; // Info
    //    [alert showEdit:self title:@"Hello Edit" subTitle:@"This is a more descriptive info text with a edit textbox" closeButtonTitle:@"Done" duration:0.0f]; // Edit
    //    [alert showCustom:self image:[UIImage imageNamed:@"git"] color:StandardColor() title:@"Custom" subTitle:@"Add a custom icon and color for your own type of alert!" closeButtonTitle:@"OK" duration:0.0f]; // Custom
    
    //    [alert showQuestion:self title:@"Question?" subTitle:@"subtitle" closeButtonTitle:@"Dismiss" duration:0.0f];
    
    
}
