ClassTable['Sound'] = Sound.new
local class = Sound.class

--[ Redefine function to handle optional gc ]--
Sound._new = Sound.new
_sound = {}
function Sound.new( arg, collect )
  local ret = Sound._new( arg )
  _sound[ret] = collect
  return ret
end

--[  Function to run on collection ]--
function class.__gc( o )
  if _sound[o] then
    print( 'done' )
    Sound.delete( o )
    _sound[o] = nil
  end
end

print( 'Class Sound Loaded' )

