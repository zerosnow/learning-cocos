local ListView = import("..views.ListView")

local ListController = class("ListController", function()
	return display.newNode()
end)

function ListController:ctor()
	self.view_ = ListView:new():addTo(self)
	self:init()
	self.data = require("app.datas.ListData")
end

function ListController:init()
	self.view_:setTouchListener(handler(self, self.onTouchListener_))
end

function ListController:onTouchListener_( event )
	if "clicked" == event.name then 
		print(self.data[event.itemPos])
	end
end

return ListController