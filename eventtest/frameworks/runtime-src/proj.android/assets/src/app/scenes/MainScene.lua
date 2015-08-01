local Actor = import("app.models.Actor")

local TOP = 3
local MIDDLE = 2
local BOTTOM = 1
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
	local backGround = display.newColorLayer(cc.c4b(255, 255, 255, 255))
	self:addChild(backGround, BOTTOM)
    self.player = Actor:new({id = "test"})
    self.view = app:createView("ActorView", self.player)
    	:pos(display.cx, display.cy + 300)
    self:addChild(self.view, MIDDLE)
    local button = cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
    	:setButtonSize(160, 80)
    	:setButtonLabel(cc.ui.UILabel.new({text = "hpDecrease"}))
    	:onButtonPressed(function ( event )
    		event.target:setScale(1.1)
    	end)
    	:onButtonRelease(function ( event )
    		event.target:setScale(1.0)
    	end)
    	:onButtonClicked(function ( event )
    		self.player:decreaseHp(1)
    	end)
    	:pos(display.cx, display.bottom + 400)
    self:addChild(button, TOP)

    end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
