Pod::Spec.new do |s|
  s.name         = "JuDian"
  s.version      = "1.0.0"
  s.summary      = "JuDian SDK."
  s.description  = "JuDian SDK with JuDianOpenApi.xcframework."

  s.homepage     = "https://github.com/hezhuangjs/JuDian"
  s.license      = { :type => "MIT", :file => "LICENSE.txt" }
  s.author       = { "Your Name" => "your@email.com" }

  s.source       = { :git => "https://github.com/hezhuangjs/JuDian.git", :tag => "#{s.version}" }

  # 关键：设置正确的平台和 Swift 版本
  s.platform     = :ios, "12.0"
  s.swift_version = "5.0"

  # 如果是静态库
  s.static_framework = true

  # 引入 xcframework
  s.vendored_frameworks = "JuDianOpenApi.framework"

  # 添加 SDK 依赖的系统库
  s.frameworks = "Foundation", "UIKit", "Security", "CoreTelephony"

  # 如果 SDK 有 bundle 资源
  # s.resource_bundles = {
  #   "JuDianResources" => ["JuDianOpenApi.xcframework/Resources/*.bundle"]
  # }
end
