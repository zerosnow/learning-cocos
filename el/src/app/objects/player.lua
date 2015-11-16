local player = class("player", function()
	return display.newSprite("#flying1.png")
end)

function player:ctor()
	
	local body = cc.PhysicsBody:createBox(self:getContentSize(),cc.PHYSICSBODY_MATERIAL_DEFAULT, cc.p(0,0))
	body:setCategoryBitmask(0x0111)
	body:setContactTestBitmask(0x1111)
	body:setCollisionBitmask(0x1001)
	self:setTag(PLAYER_TAG)
	self:setPhysicsBody(body)
	self:getPhysicsBody():setGravityEnable(false)
	self:addAnimationCache()

end

function player:addAnimationCache()
	local animationNames = {"flying", "drop", "die"}
	local animationFrameNum = {4, 3, 4}
	for i = 1, #animationNames do
		local frames = display.newFrames(animationNames[i].."%d.png",1 ,animationFrameNum[i])
		local animation = display.newAnimation(frames, 0.5/8)
		display.setAnimationCache(animationNames[i], animation)
	end
end

function player:createProgress()
    self.blood = 100 -- 1
    local progressbg = display.newSprite("image/progress1.png") -- 2
    self.fill = display.newProgressTimer("image/progress2.png", display.PROGRESS_TIMER_BAR)  -- 3
 
    self.fill:setMidpoint(cc.p(0, 0.5))   -- 4
    self.fill:setBarChangeRate(cc.p(1.0, 0))   -- 5
    -- 6
    self.fill:setPosition(progressbg:getContentSize().width/2, progressbg:getContentSize().height/2) 
    progressbg:addChild(self.fill)
    self.fill:setPercentage(self.blood) -- 7
 
    -- 8
    progressbg:setAnchorPoint(cc.p(0, 1))
    self:getParent():addChild(progressbg)
    progressbg:setPosition(cc.p(display.left, display.top))
end
 
function player:setProPercentage(Percentage)
    self.fill:setPercentage(Percentage)  -- 9
end

function player:hit()
    local hit = display.newSprite()
    hit:setPosition(self:getContentSize().width / 2, self:getContentSize().height / 2)
    self:addChild(hit)
    local frames = display.newFrames("attack%d.png", 1, 6)
    local animation = display.newAnimation(frames, 0.3 / 6)
    local animate = cc.Animate:create(animation)
 
    local sequence = transition.sequence({
        animate,
        cc.CallFunc:create(function()
            hit:removeSelf()
        end)
    })
 
    hit:runAction(sequence)
    hit:setScale(0.6)   
end

function player:flying()
	transition.stopTarget(self)
	transition.playAnimationForever(self,display.getAnimationCache("flying"))
	-- body
end

function player:drop()
	transition.stopTarget(self)
	transition.playAnimationForever(self,display.getAnimationCache("drop"))
	-- body
end

function player:die()
	transition.stopTarget(self)
	transition.playAnimationOnce(self,display.getAnimationCache("die"))
	-- body
end



return player