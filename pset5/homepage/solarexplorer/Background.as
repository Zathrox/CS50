class Background extends MovieClip
{
	function onEnterFrame()
	{
		_x -= 1;
		if(_x < -2110)
		{
			_x = 0;
		}
	}
}