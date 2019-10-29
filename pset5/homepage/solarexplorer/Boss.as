class Boss extends MovieClip
{

	var yDirection;
	var speed;
	var shootTimer;
	var health;

	function onLoad()
	{
		health = 100;
		_root.enemyHealthMeter._visible = true;
		_root.enemyHealthMeter.bar._xscale = 100;

		yDirection = 1;
		

		_x = 700;
		_y = Math.random()*200 + 50;
		speed = 3;
		_root.ship.enemies.push(this);
		shootTimer = 0;
	}

	function onEnterFrame()
	{
		if(_x > 425)
		{
			_x -= speed;
		}
		
		_y += yDirection;
		if(yDirection == 1 && _y > 250)
		{
			yDirection = -1;
		}
		else if(yDirection == -1 && _y < 50)
		{
			yDirection = 1;
		}

		if(this.hitTest(_root.ship))
		{
			_root.ship.updateHealth(-25);
			//Attach a small explosion to the stage.
			var explosion = _root.attachMovie("SmallExplosion","SmallExplosion" + _root.getNextHighestDepth(),_root.getNextHighestDepth());
			//Position the explosion at the ship's position.
			explosion._x = _root.ship._x;
			explosion._y = _root.ship._y;
		}
		
		// --- SHOOTING LOGIC---
		//increment the shoot timer variable by one
		shootTimer +=1;
		
		//if it reaches 60 (or two seconds)
		if(shootTimer > 60)
		{
			//reset the timer back to zero so it'll start incrementing up toward 60 again
			shootTimer = 0;
			
			//And fire a MiniBossMissile (which is a seperate movie clip in the library but uses the same EnemyMissile class: it looks different but behaves the same)
			var missile = _root.attachMovie("MiniBossMissile","MiniBossMissile" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
			//position the missile at the Boss's location, but offset it, so it looks like its coming from the cannon
			missile._x = _x - 110;
			missile._y = _y - 35;
			
			//fire three more missiles. This boss shoots lots of missiles at the same time
			missile = _root.attachMovie("MiniBossMissile","MiniBossMissile" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
			missile._x = _x - 110;
			missile._y = _y - 35;
			//Set this missile's y direction to -1 so this missile will move diagonally upward.
			missile.yDirection = -1;
			
			missile = _root.attachMovie("MiniBossMissile","MiniBossMissile" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
			missile._x = _x - 110;
			missile._y = _y - 35;
			//Set this missile's y direction to 1 so this missile will move diagonally downward.
			missile.yDirection = 1;
			
			missile = _root.attachMovie("MiniBossMissile","MiniBossMissile" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
			missile._x = _x - 125;
			missile._y = _y + 45;
		}
		
		//And now we are done with all the logic that needs to happen at frame rate (30 times a second)
	}
	
	//Whenver the Boss gets hit by a missile from the hero ship this function is called (see the Missile class)
	function takeDamage()
	{
		//Subtract only 5 from the Boss's health. It will take 20 hits to destroy him.
		health -= 5;
		//Update the enemy health meter to reflect the Boss's current percent health
		_root.enemyHealthMeter.bar._xscale = health;
		
		//If the Boss's health reaches zero
		if(health <=0)
		{
			//Kill it.
			explode();
		}
	}
	
	//This function is called form the Boss's takeDamage() function when it's health reaches zero
	function explode()
	{
		//First hide the enemy health meter
		_root.enemyHealthMeter._visible = false;

		//Attach 3 explosions to stage around the position of the Boss
		var explosion = _root.attachMovie("Explosion","Explosion" + _root.getNextHighestDepth(),_root.getNextHighestDepth());
		explosion._x = _x;
		explosion._y = _y;
		//Explosion 2
		explosion = _root.attachMovie("Explosion","Explosion" + _root.getNextHighestDepth(),_root.getNextHighestDepth());
		explosion._x = _x + 30;
		explosion._y = _y - 10;
		//Explosion 3
		explosion = _root.attachMovie("Explosion","Explosion" + _root.getNextHighestDepth(),_root.getNextHighestDepth());
		explosion._x = _x - 40;
		explosion._y = _y - 5;
		
		//Give the hero ship ten thousand points!
		_root.ship.updateScore(10000);
		//Update the kills stat of the hero ship.
		_root.ship.kills += 1;
		
		//Show the 10,000 point reward on screen where the Boss was.
		var rewardDisplay = _root.attachMovie("RewardPoints","RewardPoints" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
		//position the reward display at the location of the Boss
		rewardDisplay._x = _x;
		rewardDisplay._y = _y;
		// the text to reflect points won
		rewardDisplay.field.text = 10000;
		
		//Add an explosion sound fx. we create the _root.soundFX sound object in the Ship class
		_root.soundFX.attachSound("very_big_explosion.wav");
		_root.soundFX.start();
		
		//Remove the Boss graphic from stage
		this.removeMovieClip();
		
		//Since this is the final Boss, now call the heor ship's winGame() function
		_root.ship.winGame();

	}
	
}