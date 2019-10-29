class EnemyShip extends MovieClip
{
	var speed;
	var shootTimer;
	
	function onLoad()
	{
		_x = 700;
		_y = Math.random()*350 +20;
		speed = Math.random()*3 + 3;
		shootTimer = 0;
		
	}
	
	function onEnterFrame()
	{
		_x -= speed;
		if(_x < -100)
		{
			this.removeMovieClip();
		}
		
		if(this.hitTest(_root.ship.CollisionBox))
		{
			if(_root.ship.Shield._visible == false)
			{
				_root.ship.updateHealth(-20);
			}
			explode();
		}
		
		shootTimer +=1;
		if(shootTimer > 40)
		{
			shootTimer = 0;
			var missile = _root.attachMovie("EnemyMissile","EnemyMissile" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
			missile._x = _x - 50;
			missile._y = _y + 2;
		}
	}
	
	function takeDamage()
	{
		explode();
	}
		
	function explode()
	{
		var reward = _root.attachMovie("RewardPoints","RewardPoints" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
		reward._x = _x;
		reward._y = _y;
		reward.field.text = 50;
		
		var explosion = _root.attachMovie("Explosion","Explosion" + _root.getNextHighestDepth(),_root.getNextHighestDepth());
		explosion._x = _x;
		explosion._y = _y;
		this.removeMovieClip();
		_root.ship.updateScore(50);
	}
}
