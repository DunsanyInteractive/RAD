function List()
  local a = {}
  for n in pairs( _G ) do a[#a + 1] = n end
  table.sort( a )

  for i,n in ipairs( a ) do
    name = type( _G[n] )
    if name == "userdata" then
      name =  _G[n].class_name
    end
    print( string.format( "%-15s %s", n, name ) )
  end
end

function LoadLevel( arg )
  local new_env = {}
  local m = getmetatable( _G )
  if m then
    setmetatable( new_env, { __index = m.__index } )
  else
    setmetatable( new_env, { __index = _G } )
  end
  setfenv( 0, new_env )
  _G = new_env
  Game.LoadLevel( arg )
end

LoadMouse = Game.LoadMouse;
UnloadMouse = Game.UnloadMouse;

print( 'Game Loaded' )

