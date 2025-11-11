// MINASWAN!

// --------------- functions and setup ---------------

var credits_pressed = 0;
var ast_speed = 5;
var score = 0;
var health = 100;
var gametickint = 0;

function initialize_game() {
  gametickint = 0;
  score = 0;
  health = 100;
  
  setScreen("main");
  stopSound("1-menu-theme-(mp3cut.net).mp3");
  stopSound("retro-game-arcade-236133.mp3");
  playSound("video-game-boss-fiight-259885.mp3", true);
  
  game_tick();
  
  for (var i = 1; i < 4; i++) {
    spawn_asteroid(i);
  }
}

function end_game() {
  playSound("retro-game-arcade-236133.mp3", true);
  setScreen("endscreen");
  setProperty("finalscore", "text", score);
  stopSound("video-game-boss-fiight-259885.mp3");   // breaks out of the infinite game loop
}

function game_tick() {    // this loop has a set refresh rate so code.org doesn't crash with a while true loop
  setTimeout(function() {
    if (health >= 0) {
      game_tick();   // where the magic happens - recursion! only does it when health is greater than 0 (not dead.)
    } else {
      end_game();
    }
  }, 25);   // refreshes every 25 milliseconds (40 fps)
  
  setProperty("scorelabel", "text", score);   // updates score every tick (probably not the most optimized, but i don't care at this point)
  setProperty("healthbar", "value", health);   // this actually needs to update every tick because people can't be messing with it
   
  if (getProperty("ship", "y") < 250) {
    setProperty("ship", "y", 250);
  }
    
  if (getProperty("ship", "y") > 350) {
    setProperty("ship", "y", 350);
  }
  
  for (var i = 1; i < 4; i++) {   // loops through every asteroid and updates them every tick
    var sizenumber = getProperty(handler(i), "width");   // it doesn't matter whether you get width or height because both are the same, all you need is one number to calculate dynamic score
    var speedforsize = 60 / sizenumber;   // the bigger the asteroid, the slower it moves
    
    setProperty(handler(i), "y", getProperty(handler(i), "y") + ast_speed * speedforsize);    // use dynamic astroid speed as modifier
    
    if (getProperty(handler(i), "y") > 500) {
      playSound("sound://category_explosion/retro_game_enemy_shot_5.mp3");
      spawn_asteroid(i); // that is, reset asteroid and damage player
      health -= sizenumber * 0.1;
    }
    
    // getting hitboxes manually because code.org is too lazy to do it itself
    
    var left_bound = getProperty(handler(i), "x");
    var right_bound = left_bound + getProperty(handler(i), "width");    // code.org doesn't understand bounds, so we make our own
    
    var laser_x = getProperty("laser1", "x") + (getProperty("laser1", "x") / 2);    // needs to be centered
    
    if (laser_x >= left_bound && laser_x <= right_bound && getProperty("laser1", "hidden", false)) {    // if the laser is hitting the astroid
      playSound("pixel-explosion-319166.mp3");
      score += Math.round(sizenumber / 3);    // math.round() makes it nice and even
      
      hideElement(handler(i));
      spawn_asteroid(i);
    }
    
  }
  
  gametickint++;
  
  console.log("javascript sucks, i wish i was using python. game tick " + gametickint);    //mandatory javascript diss
}

function handler(id) {
  return "asteroid" + id;
}

function image_handler(id) {
  return "ast_" + id + ".png";
}

function spawn_asteroid(target) {
  setProperty(handler(target), "x", randomNumber(100, 200));
  setProperty(handler(target), "y", -100);
  setProperty(handler(target),  "image", image_handler(randomNumber(1, 4)));
  
  var size = randomNumber(25, 150);
  setProperty(handler(target), "height", size);
  setProperty(handler(target), "width", size);
  
  showElement(handler(target));
}

// ----------- startup and button handlers -------------

playSound("1-menu-theme-(mp3cut.net).mp3");

setTimeout(function() {
  showElement("byju");
  setTimeout(function() {
    showElement("playbutton");
    showElement("creditsbutton");
  }, 1000);
}, 1000);

onEvent("playbutton", "click", function() {
  initialize_game();
  
  game_tick();
  
  for (var i = 1; i < 4; i++) {
    spawn_asteroid(i);
  }
});

onEvent("main", "mousemove", function(event) {
    setProperty("ship", "x", (event.x - (getProperty("ship", "width") / 2)));   // constantly aligns ship to mouse pointer
    setProperty("ship", "y", (event.y + 25));
    
    setProperty("ship", "x", (event.x - (getProperty("ship", "width") / 2)));   // constantly aligns ship to mouse pointer
    setProperty("ship", "y", (event.y + 25));
    
    if (getProperty("ship", "y") < 250) {
      setProperty("ship", "y", 250);
    }
    
    if (getProperty("ship", "y") > 350) {
      setProperty("ship", "y", 350);
    }
});

onEvent("main", "click", function() {
  showElement("laser1");
  playSound("sound://category_projectile/retro_game_weapon_-slinky_laser_3.mp3");
  setProperty("ship", "image", "shipshoot.gif");
  setProperty("laser1", "x", (getProperty("ship", "x") + (getProperty("laser1", "width") / 2)) - 20);    // -20 at the end is a slight correction to align to middle
  setProperty("laser1", "y", getProperty("ship", "y") - 500);
  
  setTimeout(function() {
    setProperty("ship", "image", "shipstill-removebg-preview-(1).png");
    hideElement("laser1");
  }, 300);
});

onEvent("creditsbutton", "click", function() {
  setScreen("creditsscreen");
  credits_pressed++;
  
  if (credits_pressed >=5) {
    setProperty("creditslabel", "text", "YOU NEED TO STOP THAT");
    setProperty("creditslabel", "font-size", 18);
    setProperty("okcoolbutton", "text", "FINE");
  }
});

onEvent("okcoolbutton", "click", function( ) {
	if (credits_pressed >= 5) {
	  initialize_game();
	} else {
	  setScreen("startmenu");
	}
});

onEvent("againbutton", "click", function( ) {
	initialize_game();
});

onEvent("nahimgoodbutton", "click", function( ) {
	setScreen("startmenu");
	
	stopSound("retro-game-arcade-236133.mp3");
	
	playSound("1-menu-theme-(mp3cut.net).mp3");

	 setTimeout(function() {
	   showElement("byju");
	   setTimeout(function() {
	     showElement("playbutton");
     showElement("creditsbutton");
	   }, 1000);
	 }, 1000);
});

let a = document.getElementById("nahimgoodbutton");
a.addEventListener()



function string_compare(s1, s2)
{
  let check = 0
    , len = Math.min(s1.length, s2.length)
  ;

  for (let i = 0; !check && i < len; ++i)
    check = s1.charCodeAt(i) - s2.charCodeAt(i);

  return Math.sign(check || s1.length - s2.length);
}