let cnvs;

var loading = true;
var assetsToLoad = 130;
var assetsLoaded = 0;

var loadingImg = [];

let canvasWidth;
let canvasHeight;

let font;
let fontBold;

var gameStatus = 0;
var points = 0;

var maxSpeed = 7;
var minSpeed = 5.5;

var startMaxSpeed = 1;
var startMinSpeed = 1;

var timeToNextIngredient;
var timeToNextBadIngredient;
var timeDivider;
var timeDividerBad;
var ingredientsCount = 5;

var time = 0;

var choosenPizza = 0;

let arrowLeft;
let arrowRight;
let arrowRightImg;
let arrowLeftImg;

var player;
var playersImg = [];
let playersTypesCount = 9;

var playerXpos;

var ingredientsImg = [];
let ingredientsTypesCount = 22;

//layout Img
let floorImg;
let lifeImg;
let pickUpEffectImg = [];
let caption;
let pointsFrame;
let xImg;
let x2Img;
let endImg;
let endMobileImg;
let floorMobile;
let soundONImg;
let soundOFFImg;

//sounds
let clickSound;
let swipeSound;
let pickupSound;

let playGIF;

//index 0 is bad ingredient - game will be over on pickup
var playersIngredients = [[0, 11, 18, 19, 16], //4 Cheese
[10, 6, 19, 5, 2], //Chicken curry
[15, 19, 1, 20, 8], //ham garlic
[3, 20, 19, 12, 14], //ham
[16, 20, 19, 7, 5], //hot salame
[14, 19, 4, 20, 3],//mushroom
[21, 20, 19, 9, 10],//Ham & Chorizo
[2, 8, 12, 19, 13],//kebab
[19, 9, 16, 5, 7]//Salami
]

var playerWidth;
var ingredientWidth;

var pizzaNames = ["4 Cheese"/*player0*/, "Chicken Curry"/*player1*/, "Ham & Garlic Sauce"/*player2*/, "Ham"/*player3*/,
"Ham & Salami hot"/*player4*/, "Ham & Mushroom"/*player5*/, "Ham & Chorizo"/*player6*/, "Kebab"/*player7*/, "Salami"/*player8*/];
var pizzaNamesIMG = [];

var arrowMove = 0;
var arrowMoveRight = true;
var playerMove = 0;
var playerAnimCount = 6;
var playerAnimState = true;

var isVertical = false;
var wM, hM;

let soundBtn;
var muted = false;

let backBtn;

function loadingFinished(asset){
  assetsLoaded+=1;
  if(assetsLoaded>=assetsToLoad) loading = false;
}

function preload() {
  for(var i=0; i<8; i++)
    loadingImg[i] = loadImage("img/loading/loading"+(i+1).toString()+".png");
  setSizes();
}

function setup() {
  frameRate(40);
  cnvs = createCanvas(canvasWidth, canvasHeight);
  cnvs.parent("game");

  cnvs.touchStarted(mouseClicked);

  if(isVertical){
    minSpeed+=3;
    maxSpeed+=3;
  }

  //The most important game files loading - essential to go from loading to an actuall game
  playGIF = new GifBtn("img/layout/playBtn", 37);

  font = loadFont("fonts/regular.ttf", loadingFinished)
  fontBold = loadFont("fonts/bold.ttf", loadingFinished)

  caption = loadImage("img/layout/caption.png", loadingFinished);
  arrowRightImg = loadImage("img/layout/arrow.png", loadingFinished);
  arrowLeftImg = loadImage("img/layout/arrowLeft.png", loadingFinished);
  soundONImg = loadImage("img/layout/soundON.png", loadingFinished);
  soundOFFImg = loadImage("img/layout/soundOFF.png", loadingFinished);

  clickSound = loadSound('sounds/click.wav', loadingFinished);
  swipeSound = loadSound('sounds/swipe.wav', loadingFinished);

  for(var i = 0; i<ingredientsTypesCount; i++){
    ingredientsImg.push(loadImage("img/ingredients/ingredient" + i.toString() + ".png", loadingFinished));
    if(i<playersTypesCount){
      pizzaNamesIMG.push(loadImage("img/names/name"+(i+1).toString()+".png", loadingFinished));
      playersImg.push(loadImage("img/players/player" + i.toString() + ".png", loadingFinished));
    }
  }

  endImg = loadImage("img/layout/gameoverScreen.png", loadingFinished);
  endMobileImg = loadImage("img/layout/endView-Mobile.png", loadingFinished);
  floorMobile = loadImage("img/layout/floorMobile.png", loadingFinished);
  floorImg = loadImage("img/layout/floor.png", loadingFinished);
  pointsFrame = loadImage("img/layout/counterFrame.png", loadingFinished);
  xImg = loadImage("img/layout/x.png", loadingFinished);
  x2Img = loadImage("img/layout/x2.png", loadingFinished);

  for(var i=0; i<5; i++)
    pickUpEffectImg.push(loadImage("img/layout/pickupEffect/" + (i+1).toString() + ".png", loadingFinished));

  pickupSound = loadSound('sounds/pickup.wav', loadingFinished);

  arrowLeft  = new Button(arrowLeftImg)
  arrowRight  = new Button(arrowRightImg)
  soundBtn = new  Button(soundONImg);
  backBtn = new Button(x2Img);

  playAgainGIF = new GifBtn("img/layout/playAgainBtn", 36);

  var fixed = document.getElementById('game-container');

  fixed.addEventListener('touchmove', function(e) {
          e.preventDefault();
  }, false);

}


function windowResized() {
  setSizes();
  resizeCanvas(canvasWidth, canvasHeight);
}

function setSizes(){
  canvasWidth = document.getElementById("game").offsetWidth;
  canvasHeight = document.getElementById("game").offsetHeight;

  if(canvasHeight>canvasWidth) {
    isVertical = true;
    wM = canvasWidth/18;
    hM = canvasHeight/26.5;
    playerWidth = wM*6.5;
    ingredientWidth = wM*3;
  }
  else {
    isVertical = false;
    wM = canvasWidth/30;
    hM = canvasHeight/19;
    playerWidth = wM*5.5;
    ingredientWidth = wM*2.6;
  }
}

function touchMoved(event) {
  //console.log(event);
}

var aL=0;
function draw() {
  background(167, 24, 20);
  noTint();
  textFont(font);
  noStroke();
  translate(0,0);
  if(loading) {
    translate(width/2, height/2);
    image(loadingImg[aL], -wM*2, -wM*2, wM*4, wM*4)
    tint(255, 250);
    image(loadingImg[(aL+1)%8], -wM*2, -wM*2, wM*4, wM*4)
    tint(255, 230);
    image(loadingImg[(aL+2)%8], -wM*2, -wM*2, wM*4, wM*4)
    tint(255, 200);
    image(loadingImg[(aL+3)%8], -wM*2, -wM*2, wM*4, wM*4)
    tint(255, 160);
    image(loadingImg[(aL+4)%8], -wM*2, -wM*2, wM*4, wM*4)
    tint(255, 80);
    image(loadingImg[(aL+5)%8], -wM*2, -wM*2, wM*4, wM*4)
    tint(255, 50);
    image(loadingImg[(aL+6)%8], -wM*2, -wM*2, wM*4, wM*4)
    aL = (aL+1)%8;
  }
  else {
    if(gameStatus == 0) menuView();
    else if(gameStatus == 1) instructionView();
    else if(gameStatus == 2)gameView();
    else if(gameStatus == 3)endView();

    if(!isVertical){
      if (keyIsDown(LEFT_ARROW)) playerXpos-=wM*0.8;
      if (keyIsDown(RIGHT_ARROW)) playerXpos+=wM*0.8;
      soundBtn.display(wM, canvasHeight-wM*2.5, wM*1.5, wM*1.5);
    }
  }
}

function gameView(){
  noCursor();
  fill(255, 251, 210);
  noStroke();
  textAlign(CENTER, CENTER);
  textFont(fontBold);

  if(!isVertical){
    image(floorImg, wM*3, hM*17-wM*3, wM*24, wM*3);
    textSize(canvasWidth/22);
    text(points, wM*25.5, wM*0.5, wM*3.5, wM*3.5);
    image(pointsFrame, wM*25.5, wM, wM*3.5, wM*3.5);
  }else{
    image(floorMobile, 0, canvasHeight-canvasWidth/3, canvasWidth, canvasWidth/3);
    textSize(canvasWidth/10);
    text(points, wM*13.1, wM*0.5, wM*4, wM*4);
    image(pointsFrame, wM*13, wM, wM*4, wM*4);
    playerXpos=mouseX;
  }

  player.display(playerWidth, playerWidth/2);
  player.ingredients.forEach((ingredient, i) => {ingredient.display(ingredientWidth);});
  player.badIngredient.forEach((badIngredient, i) => {badIngredient.display(ingredientWidth);});

  time += 25;
}

function menuView(){
  fill(255, 251, 210);
  noStroke();
  textAlign(CENTER, CENTER);
  textFont(fontBold);

  if(Math.abs(arrowMove)>canvasWidth/100) arrowMoveRight = !arrowMoveRight;
  arrowMove += (arrowMoveRight) ? 2 : -2;
  if(!arrowLeft.over() && !arrowRight.over()) arrowMove = 0;

  if(playerAnimCount<=1){
    if(Math.abs(playerMove)>=.2) {
      playerAnimState=!playerAnimState;
      playerAnimCount++;
    }
    playerMove += playerAnimState ? 0.1 : -0.1;
  } else playerMove = 0;

  if(!isVertical){
    textSize(canvasWidth/38);
    image(caption, wM*10, hM*4, wM*10, wM*10/4);

    push();
    translate(canvasWidth/2, hM*7+wM*2);
    rotate(playerMove);
    image(playersImg[choosenPizza], -wM*3.5, -wM*2, wM*7, wM*4);
    pop();

    image(playersImg[getNextPizzaImgIndex(false)], wM*6, hM*8, wM*4, wM*2);
    image(playersImg[getNextPizzaImgIndex(true)], wM*20, hM*8, wM*4, wM*2);

    text(pizzaNames[choosenPizza], wM*9, hM*11.5, wM*12, hM*1.5);

    playGIF.display(wM*13, hM*14, wM*4, wM*4);

    arrowLeft.display(wM*8 + (arrowLeft.over() ? arrowMove : 0), hM*12, wM*3, wM*1.5);
    arrowRight.display(wM*19 + (arrowRight.over() ? arrowMove : 0), hM*12, wM*3, wM*1.5);
  }else{
    textSize(canvasWidth/17);
    image(caption, wM*1.5, hM*4, wM*15, wM*15/4);

    push();
    translate(canvasWidth/2, wM*8+wM*2);
    rotate(playerMove);
    image(playersImg[choosenPizza], -wM*4, -wM*2, wM*8, wM*4);
    pop();

    image(playersImg[getNextPizzaImgIndex(false)], wM, hM*11, wM*3.5, hM*2);
    image(playersImg[getNextPizzaImgIndex(true)], wM*13.5, hM*11, wM*3.5, hM*2);

    text(pizzaNames[choosenPizza], wM*5.5, hM*14, wM*7, hM*3)

    playGIF.display(wM*6, hM*19, wM*6, wM*6);

    arrowLeft.display(wM*2 + (arrowLeft.over() ? arrowMove : 0), hM*16.5, wM*5, wM*2.5);
    arrowRight.display(wM*11 + (arrowRight.over() ? arrowMove : 0), hM*16.5, wM*5, wM*2.5);

    mouseClicked();
  }
  cursor(CROSS);
}

function instructionView(){
  textAlign(CENTER, CENTER);
  fill(167, 24, 20);
  noStroke();
  textFont(fontBold);

  if(!isVertical){
    textSize(canvasWidth/28);
    image(pizzaNamesIMG[choosenPizza], wM*10, hM*3, wM*10, wM*10/4);

    for(var i = 0; i<5; i++){
      image(ingredientsImg[playersIngredients[choosenPizza][i]], (wM*5 + wM*4*i), ((i%2==0) ? hM*9 :  hM*7), wM*4, wM*4);
    }
    image(xImg, wM*21, hM*9, wM*4, wM*4);

    playGIF.display(wM*13, hM*14, wM*4, wM*4);

    backBtn.display(canvasWidth-wM*2.5, wM*1.5, wM*1.5, wM*1.5);
  }else{
    textSize(canvasWidth/14);
    image(pizzaNamesIMG[choosenPizza], wM*1.5, hM*4, wM*15, wM*15/4);

    image(ingredientsImg[playersIngredients[choosenPizza][0]], wM*4, hM*9, wM*5, wM*5);
    image(ingredientsImg[playersIngredients[choosenPizza][1]], wM*9, hM*9, wM*5, wM*5);
    image(ingredientsImg[playersIngredients[choosenPizza][2]], wM*2, hM*14, wM*5, wM*5);
    image(ingredientsImg[playersIngredients[choosenPizza][3]], wM*6.5, hM*14, wM*5, wM*5);
    image(ingredientsImg[playersIngredients[choosenPizza][4]], wM*11, hM*14, wM*5, wM*5);
    image(xImg, wM*11, hM*14, wM*5, wM*5);

    playGIF.display(wM*6, hM*19, wM*6, wM*6);
    backBtn.display(canvasWidth-wM*2.5, wM*1.5, wM*1.5, wM*1.5);
    mouseClicked();
  }

  cursor(CROSS);
}

function endView(){
  if(!isVertical){
    noStroke();
    image(floorImg, wM*3, hM*17-wM*3, wM*24, wM*3);

    image(endImg, wM*3.5, canvasHeight/2-wM*23/3.2, wM*23, wM*23/1.6);
    textAlign(CENTER, CENTER);
    fill(167, 24, 20);
    textSize(canvasWidth/32);
    textFont(fontBold);
    text("Game Over", canvasWidth/2, hM*7);
    textSize(canvasWidth/49);
    text("Udało ci się zebrać " + points.toString() +
    (points==1?" składnik" : ((points%10>=2 && points%10<=4) ? " składniki" : " składników")) + " możesz zrobić",
    wM*10, hM*8, wM*10);
    textSize(canvasWidth/26);
    var pizzaCount = Math.floor(points/3)
    text(pizzaCount + " Pizz" + (((pizzaCount%10>=2 && pizzaCount%10<=4) || pizzaCount==1) ? "e" : "") + "!!!", canvasWidth/2, hM*10);

    playAgainGIF.display(wM*13, hM*10, wM*4, wM*4);
  }else{
    image(floorMobile, 0, canvasHeight-canvasWidth/3, canvasWidth, canvasWidth/3);

    image(endMobileImg, wM, canvasHeight/2-wM*25.6/2, wM*16, wM*16*1.6);
    textAlign(CENTER, CENTER);
    fill(167, 24, 20);
    textSize(canvasWidth/10);
    textFont(fontBold);
    text("Game Over", canvasWidth/2, hM*8);
    textSize(canvasWidth/20);
    text("Udało ci się zebrać " + points.toString() +
    (points==1?" składnik" : ((points%10>=2 && points%10<=4) ? " składniki" : " składników")) + " możesz zrobić",
    wM*4.5, hM*10.5, wM*9);
    textSize(canvasWidth/9);
    var pizzaCount = Math.floor(points/3)
    text(pizzaCount + " Pizz" + (((pizzaCount%10>=2 && pizzaCount%10<=4) || pizzaCount==1) ? "e" : "") + "!!!", canvasWidth/2, hM*14.5);

    playAgainGIF.display(wM*6, hM*15, wM*6, wM*6);
    mouseClicked();
  }
  cursor(CROSS);
}

function mouseClicked() {
  if(gameStatus == 2) return;
  if(playGIF.over() && (gameStatus == 0 || gameStatus == 1)){
    play();
    if(!muted)clickSound.play();
  }
  if(arrowLeft.over() && gameStatus == 0){
    choosenPizza = getNextPizzaImgIndex(false);
    playerAnimCount = 0;
    if(!muted)swipeSound.play();
  }
  if(arrowRight.over() && gameStatus == 0){
    choosenPizza = getNextPizzaImgIndex(true);
    playerAnimCount = 0;
    if(!muted)swipeSound.play();
  }
  if(playAgainGIF.over() && gameStatus == 3){
    gameStatus = 0;
    if(!muted)clickSound.play();
  }
  if(soundBtn.over()){
    muted = !muted;
    soundBtn.img = muted ? soundOFFImg  : soundONImg;
    if(!muted)clickSound.play();
  }
  if(backBtn.over()){
    if(gameStatus>0) gameStatus--;
    if(!muted)clickSound.play();
  }
  mouseY = 0;
}
function mouseMoved() {
  playerXpos = mouseX;
}

function play(){
  gameStatus = (gameStatus==0) ? 1 : 2;
  player = new Player(choosenPizza, playersIngredients[choosenPizza], 4);
  player.start();

  points = 0;
  time = 0;

  startMaxSpeed = 1;
  startMinSpeed = 1;
  timeDivider = 1;
  timeDividerBad = 1;

  timeToNextIngredient = 45;
  timeToNextBadIngredient = 170;
  ingredientsCount = 5;

  if(isVertical){
    timeToNextIngredient = 50;
    timeToNextBadIngredient = 160
  }
}

function getRandomIngredientX(){
  return random(canvasWidth/10, canvasWidth-canvasWidth/7);
}

function getRandomIngredientY(){
  return random(-canvasWidth/3, -canvasWidth/4);
}

function getNextPizzaImgIndex(increment){
  return increment ? ((choosenPizza+1)%(playersTypesCount)) : ((choosenPizza > 0) ? choosenPizza-1 : playersTypesCount-1)
}

function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

class Player {
  constructor(type, ingredientTypes, typesCount){
    this.width = 0;
    this.height = 0;
    this.img = playersImg[type];

    this.ingredientstsTypes = ingredientTypes;
    this.typesCount = typesCount;

    this.ingredients = [];
    this.badIngredient = [];

    this.startPosX = canvasWidth/2 - width/2;
    this.y = 0;

    this.lastFall = 0;
    this.lastFallBad = 0;

    this.x = 0;
  }

  start(){
    for(var i=0; i<ingredientsCount; i++){
      player.ingredients.push(new Ingredient(player.ingredientstsTypes[i%(this.typesCount-1)], false));
    }
    player.badIngredient[0] = new Ingredient(player.ingredientstsTypes[4], true);
    player.badIngredient[0].fall();

  }

  display(w, h){
    this.width = w;
    this.height = h;
    this.y = (isVertical) ? canvasHeight-canvasWidth/3-h/4 : hM*17-wM*3-h/3;
    if(gameStatus == 2){
      this.x = playerXpos - w/2;
      image(this.img, this.x, this.y, w, h);

      var val = Math.floor(timeToNextIngredient/Math.sqrt(timeDivider));

      if((time/25)%Math.floor(timeToNextIngredient/Math.sqrt(timeDivider)) == 0) this.fallIngredient();
      if((time/25)%Math.floor(timeToNextBadIngredient/Math.sqrt(timeDividerBad)) == 0) this.fallBadIngredient();
    }else{
      image(this.img, this.x, this.y, w, h);
    }
  }

  fallIngredient(){
    if(gameStatus != 2) return;
    player.lastFall=getRandomInt(0, player.ingredients.length-1);
    for(var i=player.lastFall; i<player.ingredients.length; i++)
      if(!player.ingredients[i].isFalling){
        player.ingredients[i].fall();
        return;
      }
    player.addRandomIngredient();
  }

  fallBadIngredient(){
    if(gameStatus != 2 || player.badIngredient.isFalling) return;

    startMinSpeed += 0.25;
    startMaxSpeed += 0.25;
    timeDivider += 0.07;
    timeDividerBad += 0.14

    player.lastFallBad=getRandomInt(0, player.badIngredient.length-1);
    for(var i=player.lastFallBad; i<player.badIngredient.length; i++)
      if(!player.badIngredient[i].isFalling){
        player.badIngredient[i].fall();
        return;
      }
    player.badIngredient.push(new Ingredient(player.ingredientstsTypes[4], true));
  }

  addRandomIngredient(){
    if(gameStatus != 2) return;
    let type = player.ingredientstsTypes[getRandomInt(0, player.typesCount-1)];
    player.ingredients.push(new Ingredient(type, false));
    ingredientsCount++;
  }
}

class Ingredient {
  constructor(type, isBad){
    this.img = ingredientsImg[type];
    this.width = canvasWidth/7;
    this.type = type;
    this.isBad = isBad;

    this.renew();

    this.pickupEffectIndex = 0;
}

  display(w){
    this.width = w;
    if(!this.isFalling) return;
    if(!this.isPicked){
      this.standardY += this.speed;
      image(this.img, this.x, this.standardY, w, w);
      if(this.standardY > canvasHeight) {
        this.renew();
      }
      else if(this.standardY > player.y - player.width/4 &&
        this.standardY < player.y + player.width/6 &&
        this.x > player.x - w*3/4 &&
        this.x < player.x + player.width - w/4 && !this.isPicked){
        if(this.isBad) gameStatus = 3;
        else points++;

        this.isPicked = true;
        if(!muted)pickupSound.play();
      }
    }else {
      image(pickUpEffectImg[this.pickupEffectIndex], this.x-w/2, this.standardY+w/8, w*2, w*2);
      this.pickupEffectIndex++;
      if(this.pickupEffectIndex>=4) this.renew();
    }
  }

  fall(){
    this.isFalling = true;
  }

  renew(){
    this.standardY = getRandomIngredientY();
    this.x = getRandomIngredientX();
    this.isFalling = false;
    this.speed = random(minSpeed * Math.sqrt(startMinSpeed), maxSpeed * Math.sqrt(startMaxSpeed)) * canvasHeight/800;
    this.isPicked = false;
    this.pickupEffectIndex = 0;
  }
}

class Button {
  constructor(img) {
    this.x = 0;
    this.y = 0;
    this.img = img;
    this.width = 0;
    this.height = 0;
  }

  display(x, y, w, h) {
    stroke(0);
    if (this.over()) {
      tint(255, 251, 210);
      if(mouseIsPressed){
        x-=w*0.05;
        y-=h*0.05;
        w*=1.1;
        h*=1.1;
      }
    }
    else tint(255, 251, 210);
    this.x = x;
    this.y = y;
    this.width = w;
    this.height = h;
    image(this.img, x, y, w, h);
  }

  over() {
    return mouseX > this.x && mouseX < this.x + this.width && mouseY > this.y && mouseY < this.y + this.height;
  }
}

class GifBtn {
  constructor(path, frames) {
    this.img = [];
    for(var i = 0; i<frames; i++)
      this.img[i] = loadImage(path.toString()+ "/" + (i+1).toString() + ".png", loadingFinished);

    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;

    this.frames = frames;

    this.actualFrame = 0;
    this.isPlaying = false;
    this.time = 0;
    this.isDone = false;
  }

  display(x, y, w, h){
    if(mouseIsPressed && this.over()){
      x-=w*0.05;
      y-=h*0.05;
      w*=1.1;
      h*=1.1;
    }
    image(this.img[this.actualFrame], x, y, w, h);
    this.x=x;
    this.y=y;
    this.width = w;
    this.height = h;

    if(this.over()) {
      if(!this.isDone)
        this.play();
      this.isDone = true;
    }
    else {
      this.stop();
      this.isDone = false;
    }

    if(!this.isPlaying) return;
    this.time++;

    if(this.time%2!=0) return;

    if(this.actualFrame<this.frames-1)
      this.actualFrame++;
    else {
      this.stop();
    }

  }

  stop(){
    this.actualFrame = 0;
    this.isPlaying = false;
  }

  play(){
    this.isPlaying = true;
  }
  setFrame(frame){
    this.actualFrame = frame;
  }

  over() {
    return mouseX > this.x && mouseX < this.x + this.width && mouseY > this.y && mouseY < this.y + this.height;
  }
}
