--[[

"角色视图"


]]--


local ActorView = class("ActorView", function ()
	return display.newNode()
end)

function ActorView:ctor(actor)
	cc.EventProxy.new(actor, self)
		:addEventListener(actor.HP_CHANGE_EVENT, handler(self, self.onHpChange_))

	self.actor = actor
	print("1")
	self.label = cc.ui.UILabel.new({text = "start", size = 44, color = cc.c4b(100, 100, 200, 200)})
	:align(display.CENTER, 0, 0)
	:addTo(self)
	-- body
end

function ActorView:onHpChange_(event)
	self.label:setString("HP_CHANGE_EVENT")
	-- body
end


return ActorView