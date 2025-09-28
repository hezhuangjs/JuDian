

Pod::Spec.new do |spec|
  spec.name         = "JuDian"
  spec.version      = "1.0.0"
  spec.summary      = "A short description of AnyThink SDK for iOS."
  spec.description  = "JuDian is a library for xxx, which provides yyy functionality."

  spec.homepage     = "https://github.com/hezhuangjs/JuDian"
  spec.license      = { :type => "MIT", :file => "JuDian/LICENSE" }
  spec.author             = { "hezhuangjs" => "hezhuangjs@dangdang.com" }

  spec.source       = { :git => "https://github.com/hezhuangjs/JuDian.git", :tag => "#{spec.version}" }

  spec.platform     = :ios, "11.0"
  spec.swift_version = "5.0"

  spec.source_files  = "Classes", "Classes/**/*.{h,m}"
  spec.exclude_files = "Classes/Exclude"

 

end
