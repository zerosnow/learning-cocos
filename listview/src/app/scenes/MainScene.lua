local ListController = import("..controllers.ListController")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    self.ListController = ListController:new():addTo(self)

end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
