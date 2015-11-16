local lightningLayer = require("app.layers.lightningLayer")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
	local black = display.newSprite("black.jpg")
		:pos(display.cx,display.cy)
		:scale(0.5)
		:addTo(self)
	local lightningLayer = lightningLayer.new()
		:addTo(self)

end





function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
