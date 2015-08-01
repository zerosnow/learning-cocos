--[[
角色类

level

]]--

local Actor = class("Actor", cc.mvc.ModelBase)

--定义事件
Actor.HP_CHANGE_EVENT = "HP_CHANGE_EVENT"

Actor.schema = clone(cc.mvc.ModelBase.schema)
Actor.schema["hp"] = {"number", 1}

function Actor:ctor(properties, events, callbacks)
	self.super.ctor(self,properties)

end

function Actor:decreaseHp(hp)
	self:dispatchEvent({name = Actor.HP_CHANGE_EVENT})
end

return Actor