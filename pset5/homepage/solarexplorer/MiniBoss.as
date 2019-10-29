class MiniBoss extends MovieClip
{
	var speed;
	var ySpeed;
	var shootTimer;
	var health;
	
	function onLoad()
	{
		_x = 700;
		_y = Math.random()*100+100;
		speed = 2;
		ySpeed = 2;
		shootTimer = 0;
		health = 100;
		_root.enemyHealthMeter._visible = true;
		_root.enemyHealthMeter.bar._xscale = 100;
	}
	
	function onEnterFrame()
	{
		_y += ySpeed;
			if(ySpeed > 0 && _y > 250)
			{
				ySpeed *= -1;
			}
			else if(ySpeed < 0 && _y < 50)
			{
				ySpeed *= -1;
			}
		
		_x -= speed;
			if(_x < 400)
			{
				speed = 0;
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
		
		health -= 10;
		_root.enemyHealthMeter.bar._xscale = health;
		if(health <= 0)
		{
			
			explode();
		}
	}
	
	function explode()
	{
		_root.enemyHealthMeter._visible = false;
		
		var reward = _root.attachMovie("RewardPoints","RewardPoints" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
		reward._x = _x;
		reward._y = _y;
		reward.field.text = 1000;
		
		var explosion = _root.attachMovie("Explosion","Explosion" + _root.getNextHighestDepth(),_root.getNextHighestDepth());
		explosion._x = _x;
		explosion._y = _y;
		this.removeMovieClip();
		_root.ship.updateScore(1000);
	}
}