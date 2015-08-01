local ListView = class("ListView", function()
	return display.newNode()
end)

function ListView:ctor()
	display.newColorLayer(cc.c4b( 0xcc, 0xcc, 0xcc, 255))
		:addTo(self)

	local title = cc.ui.UILabel.new({text = "titleTest", size = 64, color = cc.c4b( 0xb7, 0xb7, 0xb7, 255)})
		:align(display.CENTER_TOP, display.cx, display.top - 30)
		:addTo(self)
	--local viewRect = cc.rect(0, 0, display.cx, display.cy - 200)
	
	self.lv = cc.ui.UIListView.new({
		bgColor = cc.c4b(0, 0, 255, 255),
		viewRect = cc.rect(0, 0 , display.width, display.height - 100),
		direction = cc.ui.UIScrollView.DIRECTION_VERTICAL,
		})
		:onTouch(handler(self, self.onTouchListener))
		:addTo(self)

	local data = require("app.datas.ListData")
	self:createList(data)
end

function ListView:createList( data )
	local itemWidth = 120
	local itemHeight = 50
	for i = 1, #data do
		local item = self.lv:newItem()
		local content = cc.ui.UILabel.new({text = i, size = 24, align =cc.ui.TEXT_ALIGN_CENTER, color = cc.c4b(0, 255, 0, 255)})
		item:addContent(content)
		item:setItemSize(itemWidth, itemHeight)
		self.lv:addItem(item)
	end
	self.lv:reload()
end

function ListView:setTouchListener(listener)
	self.onTouchListener_ = listener
end

function ListView:onTouchListener(event)
	if self.onTouchListener_ then 
		self.onTouchListener_(event)
	end
	-- body
end


return ListView