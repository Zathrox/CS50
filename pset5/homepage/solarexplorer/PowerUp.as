class PowerUp extends MovieClip
{
	var speed;
	var type;

	function onLoad()
	{
		speed = 2;
		type = Math.floor(Math.random()*3+1);
		_x = 650;
		_y = Math.random()*300+50;
	}

	function onEnterFrame()
	{
		_x -= speed;
		_rotation -= 5;

		if(this.hitTest(_root.ship.CollisionBox))
		{		
			if(type == 1)
			{
				_root.ship.updateHealth(100 - _root.ship.health);
			}
			if(type == 2)
			{
				for(var i in _root.ship.enemies)
				{
					_root.enemyHealthMeter._visible = false;
					_root.ship.enemies[i].explode();
				}
			}
			if(type == 3)
			{
				_root.ship.Shield._visible=true;
			}
			this.removeMovieClip();
		}
		if( _x < -30 )
		{
			this.removeMovieClip();
		}
	}
}