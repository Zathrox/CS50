class EnemyMissile extends MovieClip
{
	var speed;
	
	function onLoad()
	{
		speed = -15;
	}
	
	function onEnterFrame()
	{
		_x += speed;

		if(this.hitTest( _root.ship.CollisionBox) )
		{
			this.removeMovieClip();
			if(_root.ship.Shield._visible == false)
			{
				_root.ship.updateHealth(-10);
			}
		}
		
		if(_x < 0)
		{
			this.removeMovieClip();
		}
	}
}