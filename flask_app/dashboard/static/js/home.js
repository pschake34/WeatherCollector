var root = document.querySelector(':root');
var lowerLimit = -20;
var upperLimit = 120;
var u = upperLimit - lowerLimit;
var radius = 51;
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
    x = Math.sqrt((radius*radius)-(y*y));
    if (temp > (((upperLimit+lowerLimit) / 2))) {
        return x;
    } else {
        return -1 * x;
    }
}

function computeAngle(temp, y) {
    angle = toDegrees(Math.asin((y * Math.sin(toRadians(90))) / radius));
    console.log(angle)
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
    root.style.setProperty('--pointertop', 50 - y + "%");
    root.style.setProperty('--pointerleft', 50 + x + "%");
    root.style.setProperty('--pointerdeg', 90-angle + "deg");
}