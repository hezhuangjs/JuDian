//
//  JuDianOpenApi.h
//  JuDianOpenApi
//
//  Created by 辞书_褚平欧 on 2023/7/11.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <JuDianOpenApi/JuDianShowConfig.h>
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, JuDianError) {       //网络请求异常，code = 0时，status返回下列错误枚举
    JuDianErrorRequestTimeOut       =   -1001,  //请求超时
    JuDianErrorNetworkOffline       =   -1002,  //网络已断开,请检查本地网络连接
    JuDianErrorCertificateInvalid   =   -1003,  //证书异常,请检查本机系统时间
    JuDianErrorAuthError            =   -1004,  //权限不正确，请检查SDK token
    JuDianErrorUndefined            =   -1009,  //暂时未定位问题,请稍后再试,有问题请联系:https://judian.jdapi.com
};

typedef NS_ENUM(NSUInteger, JuDianViewDirection){
    JuDianDirectionLeftUP           =   0,      //指定原点为左上原点，向下绘制
    JudianDirectionLeftDown         =   1,      //指定原点为左下原点，向上绘制
};

@interface JuDianOpenApi : NSObject

/// 初始化SDK
/// - Parameter token: 管理后台提供的聚典token
+ (void)initWithToken:(NSString *)token;

#pragma mark -- 新版功能，根据库查询，合并去重书籍

/// 查询词条，返回结果  库查询返回结果
/// - Parameters:
///   - word: 查询的字词
///   - fields: 需要查询的库，不传或为空时，默认极速模式
///   例如 语词库: shiwen.yuci 百科库:shiwen.baike 诗词库:shici 如果只查询百科 则传@[@shiwen.baike"] 同时查询语词与百科 则传@[@"shiwen.baike",@"shiwen.yuci"]
///   具体对应库名可以通过getAuthList 获取:  info.danzi:基本信息-单字  shici:唐诗宋词 shiwen.baike:释文-百科 shiwen.danzi:释文-单字 shiwen.yuci:释文-语词 shufa:书法 yuanliu：源流
///   ps:极速模式下，语词百科仅返回释文，单字返回释文与单字基本信息。如果所查词条没有释文，则返回最匹配的一个库的数据。其余库中如果有数据，会在返回体中返回一个lazyFields数组，数组中为当前所查词有相关信息的其他库
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
///   success response:{
///     code:200
///     body:{
///         fields:{}//包含此词条的数据库与库名
///         lazyFields:[]//当前请求中未返回的数据库库名
///         font:{}//字体信息
///         data:{}//词条数据
///     }
/// }
///   failure response : {
///   code : NSInteger
///   body : {
///     status: Integer  //返回的错误码，为0时返回JuDianErrorInteger
///     detail: String //错误的主要描述信息
///     ...
///     }
///   }
+ (void)getExplainWithWord:(NSString *)word
                    fields:(nullable NSArray *)fields
              successBlock:(void(^)(NSDictionary * response))success
              failureBlock:(void(^)(NSDictionary * response))failure;

/// 获取配置的可查询书籍列表与数据库
/// - Parameters:
///   - word: 查询的字词
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
///   success response:{
///     code:200
///     body:{
///         books:[@{name:书本名,id:书本id}]返回的书籍数组
///         fields:@{}
///     }
/// }
///   failure response : {
///   code : NSInteger
///   body : {
///     status: Integer  //返回的错误码，为0时返回JuDianErrorInteger
///     detail: String //错误的主要描述信息
///     ...
///     }
///   }
+ (void)getAuthListSuccessBlock:(void(^)(NSDictionary * response))success
                   failureBlock:(void(^)(NSDictionary * response))failure;

/// 查询词条，并在指定位置绘制结果视图 结果根据库查询返回
/// - Parameters:
///   - word: 查询的字词
///   - direction: 页面绘制方向
///   - origin: 页面绘制起点
///   - width: 绘制页面的宽度
///   - height: 绘制页面的最大高度
+ (void)showExplainViewWithWord:(NSString *)word
                      direction:(JuDianViewDirection)direction
                         origin:(CGPoint)origin
                          width:(CGFloat)width
                      maxHeight:(CGFloat)height;

#pragma mark -- 同旧版功能，根据书籍查询

/// 根据书本id获取指定书本中关于词条word的释义，返回系统中查询到的数据
/// - Parameters:
///   - word: 查询的词条
///   - books: 指定的书籍id 不传或为空时，默认搜索所有书籍数据
///   例如 现代汉语大词典 id:40 辞海(第7版) id:98  如果只查询辞海 books:@[@"98"] 同时查询辞海与汉语大词典books:@[@"40",@"98"]或@[@40,@98]
///   books中数据可为NSString 或 NSNumber
///   - isFast: ture为快速检索，no为普通查询，快速检索时仅返回第一条匹配数据，普通查询时返回查询到的所有数据
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getExplainWithWord:(NSString *)word
                     books:(nullable NSArray *)books
                fastSearch:(BOOL)isFast
              successBlock:(void(^)(NSDictionary * response))success
              failureBlock:(void(^)(NSDictionary * response))failure;


/// 获取单字信息
/// - Parameters:
///   - word: 查询的词条
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getStrokeOrderForWord:(NSString *)word
                 successBlock:(void(^)(NSDictionary * response))success
                 failureBlock:(void(^)(NSDictionary * response))failure;

/// 定性语查询，返回词条是否包含历史纪年、古今地名、中译英、英译中
/// - Parameters:
///   - word: 查询的词条
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)cheackWordContainer:(NSString *)word
               successBlock:(void(^)(NSDictionary * response))success
               failureBlock:(void(^)(NSDictionary * response))failure;

/// 获取历史纪年信息数据
/// - Parameters:
///   - word: 查询的词条
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getHistoricalYearWithWord:(NSString *)word
                     successBlock:(void(^)(NSDictionary * response))success
                     failureBlock:(void(^)(NSDictionary * response))failure;

/// 获取古今地名数据:根据关键字搜索古今地名列表,最多100条数据
/// - Parameters:
///   - word: 查询的词条
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getAncientPlaceWithWord:(NSString *)word
                   successBlock:(void(^)(NSDictionary * response))success
                   failureBlock:(void(^)(NSDictionary * response))failure;

/// 英译中：精确查询英语的释文，接口返回的部分内容是乱码需要下载对应的字体包才能显示
/// - Parameters:
///   - word: 查询的词条
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getEnglishExplainWithWord:(NSString *)word
                     successBlock:(void(^)(NSDictionary * response))success
                     failureBlock:(void(^)(NSDictionary * response))failure;

/// 中译英：精确查询汉字的英语释文，接口返回的部分内容是乱码需要下载对应的字体包才能显示
/// - Parameters:
///   - word: 查询的词条
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getChineseToEnglishWithWord:(NSString *)word
                       successBlock:(void(^)(NSDictionary * response))success
                       failureBlock:(void(^)(NSDictionary * response))failure;

/// 词头模糊搜索：根据词头模糊搜索得到列表，通过headword再调用内容/释文接口。高亮里面包含headword、simplified
/// - Parameters:
///   - word: 查询的词条
///   - size: 一次查询返回的最大条目数，最大100
///   - page: 请求的页码，0开始
///   - books: 指定的书籍id 不传或为空时，默认搜索所有书籍数据
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getBookExplainHeadword:(NSString *)word
                          size:(NSInteger)size
                          page:(NSInteger)page
                         books:(nullable NSArray *)books
                  successBlock:(void(^)(NSDictionary * response))success
                  failureBlock:(void(^)(NSDictionary * response))failure;

/// 模糊搜索释文：根据释文模糊搜索得到列表，通过headword再调用内容/释文接口。高亮里面包含text、headword、simplified
/// - Parameters:
///   - word: 查询的词条
///   - size: 一次查询返回的最大条目数，最大100
///   - page: 请求的页码，0开始
///   - books: 指定的书籍id 不传或为空时，默认搜索所有书籍数据
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getBookExplainExplain:(NSString *)word
                         size:(NSInteger)size
                         page:(NSInteger)page
                        books:(nullable NSArray *)books
                 successBlock:(void(^)(NSDictionary * response))success
                 failureBlock:(void(^)(NSDictionary * response))failure;

/// 全文模糊搜索：会同时搜索词头和释文得到列表，通过headword再调用内容/释文接口。高亮里面包含text、headword、simplified
/// - Parameters:
///   - word: 查询的词条
///   - size: 一次查询返回的最大条目数，最大100
///   - page: 请求的页码，0开始
///   - books: 指定的书籍id 不传或为空时，默认搜索所有书籍数据
///   - success: 查询成功并返回结果
///   - failure: 查询失败返回错误信息
+ (void)getBookExplainFuzzy:(NSString *)word
                       size:(NSInteger)size
                       page:(NSInteger)page
                      books:(nullable NSArray *)books
               successBlock:(void(^)(NSDictionary * response))success
               failureBlock:(void(^)(NSDictionary * response))failure;

@end

NS_ASSUME_NONNULL_END
