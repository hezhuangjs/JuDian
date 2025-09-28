

Pod::Spec.new do |spec|
  spec.name         = "JuDian"
  spec.version      = "1.0.0"
  spec.summary      = "A short description of AnyThink SDK for iOS."
  spec.description  = <<-DESC
                    A longer description of MySDK in Markdown format.
                   DESC
  spec.homepage     = "https://github.com/hezhuangjs/JuDian"
  spec.license      = { :type => "MIT", :file => "JuDian/LICENSE" }
  spec.author             = { "hezhuangjs" => "hezhuangjs@dangdang.com" }
  spec.source       = { :git => "https://github.com/hezhuangjs/JuDian.git", :tag => "#{spec.version}" }
  spec.platform     = :ios, "11.0"
  spec.static_framework = true
  spec.vendored_frameworks = "JuDianOpenApi.xcframework"
  spec.frameworks = "Foundation", "UIKit", "Security", "CoreTelephony"

end
