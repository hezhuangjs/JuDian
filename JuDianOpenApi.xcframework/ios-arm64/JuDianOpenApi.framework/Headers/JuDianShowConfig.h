//
//  JuDianShowConfig.h
//  JuDianOpenApi
//
//  Created by 辞书_褚平欧 on 2023/7/27.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface JuDianShowConfig : NSObject

//-----实例化单例-----
+ (JuDianShowConfig *)defaultConfig;


//-----字体-----
//查询词的字体大小 默认:17
@property (nonatomic , assign) NSInteger titleFontSize;

//释义、历史纪年 默认:15
@property (nonatomic , assign) NSInteger segFontSize;

//查询词拼音字体 默认:15
@property (nonatomic , assign) NSInteger spellFontSize;

//结果释义条目 默认:16
@property (nonatomic , assign) NSInteger listFontSize;

//来源介绍字体 默认:12
@property (nonatomic , assign) NSInteger sourceFontSize;

//-----颜色-----
//查询词的字体颜色 默认:0xFFFFFF
@property (nonatomic , strong) UIColor * titleColor;

//结果释义条目字体颜色 默认:0xFFFFFF
@property (nonatomic , strong) UIColor * listColor;

//来源介绍字体颜色 默认:0xFFFFFF
@property (nonatomic , strong) UIColor * sourceColor;

//释义弹出框颜色 默认:0x000000 alpha:0.8
@property (nonatomic , strong) UIColor * showBG;

//-----功能-----
//开启打印 默认不开启
@property (nonatomic , assign) BOOL openLog;
//开启错误信息打印 默认不开启
@property (nonatomic , assign) BOOL errorLog;

@end

NS_ASSUME_NONNULL_END
