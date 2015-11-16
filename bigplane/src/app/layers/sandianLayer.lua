curDetail = 5

sandianLayer = class("sandianLayer", function()
	return display.newLayer()
end)

function sandianLayer:ctor()
	-- body
	local r = 200
	local x = math.random(-r,r)
	local signy = math.random(-1,1)
	local y = math.sqrt(r*r - x*x)
	if signy < 0 then
		y = -y
	end
	self:drawLight(display.cx+200,display.cy+50,display.cx +200 + x,display.cy + 50 + y,200)
end

function sandianLayer:drawLight(x1, y1, x2, y2, displace)
	if displace < curDetail then
		local shape3 = display.newLine({{x1,y1},{x2,y2}},{borderColor = cc.c4f(0, 0.3, 0.8, 0.7),borderWidth = 3})
			:addTo(self)
	else
		local mid_x = (x2+x1)/2
		local mid_y = (y2+y1)/2
		local midx = mid_x + (math.random(0,1)-0.5)*displace
		local midy = mid_y + (math.random(0,1)-0.5)*displace
		self:drawLight(x1,y1,midx,midy,displace/2)
		self:drawLight(x2,y2,midx,midy,displace/2)
	end
end


return sandianLayer