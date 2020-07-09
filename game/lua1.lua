object = {}

local a = 2
local b = 3

function object:OnUpdate()
	ConsoleSystem.PrintInfo( "sss: " .. a + b )
	
	if not ResourceSystem.LoadMesh( "axe", "models/axe.mdl" ) then
		ConsoleSystem.PrintError( "You loh, lol" )
	end
end

function object:OnStart()
end