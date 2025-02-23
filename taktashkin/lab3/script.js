document.getElementById('setAlarm').addEventListener('click', setAlarm);
document.getElementById('stopAlarm').addEventListener('click', stopAlarm);

let alarmInterval;
let alarmTime;

function setAlarm()
{
    const timeInput = document.getElementById('alarmTime').value;
    if (!timeInput)
    {
        alert('Пожалуйста, установите время будильника.');
        return;
    }
    
    const now = new Date();
    const [hours, minutes] = timeInput.split(':');
    alarmTime = new Date(now.getFullYear(), now.getMonth(), now.getDate(), hours, minutes);
    
    if (alarmTime <= now) {
        alert('Пожалуйста, установите время в будущем.');
        return;
    }
    
    const timeUntilAlarm = alarmTime - now;
    setTimeout(startAlarm, timeUntilAlarm);
    
    document.getElementById('setAlarm').disabled = true;
    document.getElementById('stopAlarm').disabled = false;
}

function startAlarm()
{
    alarmInterval = setInterval(changeBackgroundColor, 500);
    alert('Будильник сработал!');
}

function stopAlarm() 
{
    clearInterval(alarmInterval);
    document.body.style.backgroundColor = '';
    document.getElementById('setAlarm').disabled = false;
    document.getElementById('stopAlarm').disabled = true;
}

function changeBackgroundColor() 
{
    const randomColor = '#' + Math.floor(Math.random() * 16777215).toString(16);
    document.body.style.backgroundColor = randomColor;
}
