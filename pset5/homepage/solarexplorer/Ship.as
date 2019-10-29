class Ship extends MovieClip
{
	var velocity;
	var shootLimiter;
	var enemyTimer;
	var enemies;
	var score;
	var health;
	var powerupTimer;
	var miniBossTimer;
	var bossCountdown;
	var shaking;
	var shakeDuration;
	
	function onLoad()
	{

		_root.ship.Shield._visible = false;
		_root.enemyHealthMeter._visible = false;
		_root.gameOverMenu._visible = false;
		_root.gameOverMenu.playAgainButton.onPress = function()
		{
			_root.ship.newGame();
		}
		_visible = false;
		_root.gameOverMenu._visible = false;
		_root.healthMeter._visible = false;
		_root.playMenu.playButton.onPress = function()
		{
			_root.ship.newGame();
		}
	}
	
	function newGame()
	{
		_root.playMenu._visible = false;
		_root.gameOverMenu._visible = false;
		_root.enemyHealthMeter._visible = false;

		//Reset Values
		velocity = 10;
		shootLimiter = 0;
		enemyTimer = 0;
		powerupTimer = 0;
		miniBossTimer = 0;
		bossCountdown = 3;
		enemies = [];

		_x = 300;
		_y = 200;
		
		_visible = true;
		shaking = false;
		shakeDuration = 10;
		_rotation = 0;
		resetHealth();
		resetScore();	
	}
	
	//= Explosion Commands
	function explode()
	{
		this._visible = false;
		var explosion = _root.attachMovie("Explosion", "Explosion" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
		explosion._x = _x;
		explosion._y = _y;
		for(var i in enemies)
		{
			enemies[i].explode();
		}
		gameOver();
	}
	
	//= Health Related Functions
	function updateHealth(points)
	{
		health += points;
		if(health < 1)
		{
			health = 0;
			explode();
		}
		_root.healthMeter.bar._xscale = health;
	}
	
	//This function gets called from the Boss class when the Boss is destroyed. Kill the boss to win the game.
	function winGame()
	{
		this._visible = false;
		explode();
		gameOver();
	}
	
	function gameOver()
	{
		_root.gameOverMenu._visible=true;
		_root.gameOverMenu.playAgainButton.onPress = function()
		{
			_root.ship.newGame();
		}
	}

	function resetHealth()
	{
		health = 100;
		_root.healthMeter._visible = true;
		_root.healthMeter.bar._xscale = 100;
	}
	
	//= Score Related Functions
	function resetScore()
	{
		score = 0;
		_root.scoreText.text = score;
	}
	function updateScore(points)
	{
		score += points;
		_root.ScoreText.text = score;
	}
	function initShake()
	{
		shaking = true;
		shakeDuration = 10;
		_rotation = 5;
	}
	
	function shake()
	{
		_rotation *= -1;
		shakeDuration -= 1;
		if(shakeDuration == 0)
		{
			shaking = false;
			_rotation = 0;
		}
	}
	
	//= Ship Controls and Functions
	function onEnterFrame()
	{
		if(_visible == true)
		{
			shootLimiter += 1;
			if( Key.isDown(Key.RIGHT) ) { _x = _x + velocity;}
			if( Key.isDown(Key.LEFT) ) {_x = _x - velocity;}
			if( Key.isDown(Key.UP) ) {_y = _y - velocity;}
			if( Key.isDown(Key.DOWN) ) {_y = _y + velocity;}
			if( Key.isDown(Key.SPACE) && shootLimiter > 8 )
			{
				shootLimiter = 0;
				var missile = _root.attachMovie( "Missile" , "Missile" + _root.getNextHighestDepth() , _root.getNextHighestDepth() );
				missile._x = _x + 65;
				missile._y = _y + 15;
			}
			
			enemyTimer += 1;
			if(enemyTimer > 60)
			{
				enemyTimer = 0;
				var enemy = _root.attachMovie("EnemyShip", "EnemyShip" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
				enemies.push(enemy);
			}
			
			if(shaking == true){ shake(); }
			
			if(!_root.miniBoss)
			{
				miniBossTimer += 1;
				if(miniBossTimer > 300)
				{
					miniBossTimer = 0;
					if( bossCountdown == 0)
					{
						var enemy = _root.attachMovie("Boss", "boss", _root.getNextHighestDepth());
						enemies.push(enemy);

					}
					else
					{
						var enemy = _root.attachMovie("MiniBoss", "miniBoss", _root.getNextHighestDepth());
						enemies.push(enemy);
						bossCountdown -= 1;
					}
				}
			}
			
			powerupTimer += 1;
			if(powerupTimer > 150)
			{
				powerupTimer = 0;
				var powerup = _root.attachMovie("PowerUp", "PowerUp" + _root.getNextHighestDepth(), _root.getNextHighestDepth());
			}
			
			if(_root.ship.Shield._visible == true)
			{
				_root.ship.Shield._alpha -= .5;
				if(_root.ship.Shield._alpha < 0)
				{
					_root.ship.Shield._visible = false;
					_root.ship.Shield._alpha = 100;
				}
			}
		}
	} 
}
