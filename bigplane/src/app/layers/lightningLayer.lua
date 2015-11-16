
local curDetail = 5
BALL_LIGHTNING = 1
LINE_LIGHTNING = 2
TWO_LIGHTNING = 3

local lightningLayer = class("lightningLayer", function()
	return display.newLayer()
end)

function lightningLayer:ctor(points, type, param)
	self.points = points
	self.type = type
	self.param = param
	math.randomseed(os.time())
	layer = {}
	layerNum = 0
	self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, handler(self, self.refreshLayer))
	self:scheduleUpdate()

	-- body
end

function lightningLayer:create()
	local node = display.newNode()
	local r = 200
	local x = math.random(-r,r)
	local signy = math.random(-1,1)
	local y = math.sqrt(r*r - x*x)
	if signy < 0 then
		y = -y
	end
	self:drawLight(display.cx+200,display.cy+50,display.cx +200 + x,display.cy + 50 + y,200,node)
	dump(node, "node")
	return node
end

function lightningLayer:drawLight(x1, y1, x2, y2, displace, node)
	if displace < curDetail then
		local shape3 = display.newLine({{x1,y1},{x2,y2}},{borderColor = cc.c4f(0, 0.3, 0.8, 0.7),borderWidth = 3})
		node:addChild(shape3)
	else
		local mid_x = (x2+x1)/2
		local mid_y = (y2+y1)/2
		local midx = mid_x + (math.random(0,1)-0.5)*displace
		local midy = mid_y + (math.random(0,1)-0.5)*displace
		self:drawLight(x1,y1,midx,midy,displace/2)
		self:drawLight(x2,y2,midx,midy,displace/2)
	end
end

function lightningLayer:refreshLayer()
	layerNum = layerNum + 1
	print(layerNum)
	if layerNum > 10 then
		dump(layer[layerNum-1],"layer[]")
		--layer[1]:removeSelf()
		table.remove(layer,1)
		layerNum = layerNum - 1
	end
	layer[layerNum] = self:create()
		:addTo(self)
	-- body
end

return lightningLayer