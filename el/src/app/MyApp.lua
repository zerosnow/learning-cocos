
require("config")
require("cocos.init")
require("framework.init")
require("app.layers.BackgroundLayer")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")
    display.addSpriteFrames("image/player.plist", "image/player.pvr.ccz")
    cc.Director:getInstance():setContentScaleFactor(640/CONFIG_SCREEN_HEIGHT)
    math.randomseed(os.time())
    self:enterScene("MainScene")
end

return MyApp
