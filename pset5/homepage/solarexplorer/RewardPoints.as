class RewardPoints extends MovieClip
{
	function onEnterFrame()
	{
		_alpha -= 2;
		if(_alpha < 0)
		{
			this.removeMovieClip();
		}
	}
} 