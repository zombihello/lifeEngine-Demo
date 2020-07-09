object = {}

local a = 5
local b = 6

function object:OnUpdate()
	printMessage( "lua2: " .. a + b )
end

function object:OnStart()
	
end