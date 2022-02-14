var root = document.querySelector(':root');
var lowerLimit = -20;
var upperLimit = 120;
var u = upperLimit - lowerLimit;
var radius = 53;
var transform = radius / 3;

function toRadians (angle) {
    return angle * (Math.PI / 180);
}

function toDegrees (radians) {
    return radians * (180 / Math.PI);
}

function computeY(temp) {
    return -(radius - transform) * Math.cos(toRadians((Math.abs(temp - lowerLimit) / u) * 360)) + transform;
}

function computeX(temp, y) {
    x = Math.sqrt((0.71) * ((radius*radius)-(y*y)));
    if (temp > (((upperLimit+lowerLimit) / 2))) {
        return x;
    } else {
        return -1 * x;
    }
}

function computeAngle(temp, y) {
    angle = toDegrees(Math.asin((y * Math.sin(toRadians(90))) / radius));
    if (temp > (((upperLimit+lowerLimit) / 2))) {
        return angle;
    } else {
        return 180 - angle;
    }
}

function setTempGuage(temp) {
    y = computeY(temp);
    x = computeX(temp, y);
    angle = computeAngle(temp, y);
    console.log("X: " + x + "\nY: " + y + "\nDeg: " + angle);
    console.log(temp);
    root.style.setProperty('--pointertop', 50 - y + "%");
    root.style.setProperty('--pointerleft', 47 + x + "%");
    root.style.setProperty('--pointerdeg', 90-angle + "deg");
}

async function getData(type) {
    let url = '/get_sensor_data/' + type;    
    let obj = null;
    
    try {
        obj = await (await fetch(url)).json();
    } catch(e) {
        console.log('error');
    }

    return Object.values(obj)[0];
}

async function main() {
    var temperatureF = await getData("temperature");
    var temperatureC = (temperatureF - 32) * (5/9);
    var humidity = await getData("humidity");
    var pressureInHg = await getData("pressure");
    var pressureHPa = pressureInHg * 33.86389;
    var pressureAtm = pressureInHg / 29.921;
    var windSpeed = await getData("wind-speed");

    setTempGuage(temperatureF)
    document.getElementById("temperature-F").innerHTML = temperatureF.toFixed(1) + "°F";
    document.getElementById("temperature-C").innerHTML = temperatureC.toFixed(1) + "°C";
    document.getElementById("humidity").innerHTML = humidity.toFixed(1) + "%";
    document.getElementById("pressure-inHg").innerHTML = pressureInHg.toFixed(2) + " inHg";
    document.getElementById("pressure-hPa").innerHTML = pressureHPa.toFixed(1) + " hPa";
    document.getElementById("pressure-atm").innerHTML = pressureAtm.toFixed(3) + " atm";
    document.getElementById("wind-speed").innerHTML = windSpeed.toFixed(1) + " Mph";

    setTimeout(main, 10000);  //run every 10 seconds
}