document.getElementById('setAlarm').addEventListener('click', setAlarm);
document.getElementById('stopAlarm').addEventListener('click', stopAlarm);

let alarmInterval;
let blinkInterval;
let alarms = []; // Массив для хранения будильников
let alarmCounter = 1; // Счетчик будильников

/**
 * Устанавливает будильник на указанное время.
 * Если время не указано или установлено в прошлом, выводит предупреждение.
 * Добавляет будильник в таблицу.
 * 
 * @returns {void}
 */
function setAlarm() {
    const timeInput = document.getElementById('alarmTime').value;
    if (!timeInput) {
        alert('Пожалуйста, установите время будильника.');
        return;
    }
    
    const now = new Date();
    const [hours, minutes] = timeInput.split(':');
    const alarmTime = new Date(now.getFullYear(), now.getMonth(), now.getDate(), hours, minutes);
    
    if (alarmTime <= now) {
        alert('Пожалуйста, установите время в будущем.');
        return;
    }
    
    const timeUntilAlarm = alarmTime - now;

    // Добавляем будильник в массив
    const alarm = {
        id: alarmCounter++,
        time: alarmTime,
        status: 'Ожидание',
        blinkDuration: 500, // Время мигания в миллисекундах
        blinkEndTime: null // Время окончания мигания
    };
    alarms.push(alarm);

    // Добавляем будильник в таблицу
    addAlarmToTable(alarm);

    // Запускаем таймер для обновления времени до срабатывания и времени мигания
    startTimer(alarm);

    // Запускаем таймер для срабатывания будильника
    setTimeout(() => startAlarm(alarm), timeUntilAlarm);

    // Разблокируем кнопку "Установить будильник"
    document.getElementById('setAlarm').disabled = false;
}

/**
 * Запускает будильник: начинает менять цвет фона страницы.
 * Обновляет статус будильника в таблице.
 * 
 * @param {Object} alarm - Объект будильника.
 * @returns {void}
 */
function startAlarm(alarm) {
    // Устанавливаем время окончания мигания (5 секунд с текущего момента)
    alarm.blinkEndTime = new Date(Date.now() + 5000);

    // Включаем мигание фона
    blinkInterval = setInterval(() => changeBackgroundColor(alarm.blinkDuration), alarm.blinkDuration);

    // Останавливаем мигание через 5 секунд
    setTimeout(() => {
        clearInterval(blinkInterval);
        document.body.style.backgroundColor = ''; // Возвращаем фон в исходное состояние
        updateAlarmStatus(alarm.id, 'Завершен');
    }, 5000); // 5 секунд

    // Обновляем статус будильника
    updateAlarmStatus(alarm.id, 'Сработал');

    // Разблокируем кнопку "Остановить будильник"
    document.getElementById('stopAlarm').disabled = false;
}

/**
 * Останавливает будильник: прекращает изменение цвета фона и сбрасывает настройки кнопок.
 * 
 * @returns {void}
 */
function stopAlarm() {
    clearInterval(blinkInterval); // Останавливаем мигание
    document.body.style.backgroundColor = ''; // Возвращаем фон в исходное состояние
    document.getElementById('stopAlarm').disabled = true; // Блокируем кнопку "Остановить будильник"

    // Обновляем статус всех активных будильников на "Остановлен"
    alarms.forEach(alarm => {
        if (alarm.status === 'Сработал') {
            updateAlarmStatus(alarm.id, 'Остановлен');
        }
    });
}

/**
 * Меняет цвет фона страницы на случайный.
 * 
 * @param {Number} duration - Время мигания в миллисекундах.
 * @returns {void}
 */
function changeBackgroundColor(duration) {
    const randomColor = '#' + Math.floor(Math.random() * 16777215).toString(16);
    document.body.style.backgroundColor = randomColor;
}

/**
 * Добавляет будильник в таблицу.
 * 
 * @param {Object} alarm - Объект будильника.
 * @returns {void}
 */
function addAlarmToTable(alarm) {
    const tableBody = document.querySelector('#alarmTable tbody');
    const row = document.createElement('tr');

    row.innerHTML = `
        <td>${alarm.id}</td>
        <td class="time-until">${formatTimeUntilAlarm(alarm.time)}</td>
        <td>${alarm.status}</td>
        <td class="blink-time">${formatBlinkTime(alarm.blinkEndTime)}</td>
    `;

    tableBody.appendChild(row);
}

/**
 * Обновляет статус будильника в таблице.
 * 
 * @param {Number} id - Идентификатор будильника.
 * @param {String} status - Новый статус будильника.
 * @returns {void}
 */
function updateAlarmStatus(id, status) {
    const rows = document.querySelectorAll('#alarmTable tbody tr');
    rows.forEach(row => {
        if (row.cells[0].textContent == id) {
            row.cells[2].textContent = status;
        }
    });
}

/**
 * Форматирует время до срабатывания будильника.
 * 
 * @param {Date} alarmTime - Время срабатывания будильника.
 * @returns {String} - Время до срабатывания в формате "часы:минуты:секунды".
 */
function formatTimeUntilAlarm(alarmTime) {
    const now = new Date();
    const diff = alarmTime - now;

    const hours = Math.floor(diff / (1000 * 60 * 60));
    const minutes = Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((diff % (1000 * 60)) / 1000);

    return `${hours}:${minutes}:${seconds}`;
}

/**
 * Форматирует оставшееся время мигания.
 * 
 * @param {Date} blinkEndTime - Время окончания мигания.
 * @returns {String} - Оставшееся время мигания в формате "часы:минуты:секунды".
 */
function formatBlinkTime(blinkEndTime) {
    if (!blinkEndTime) return '00:00:00'; // Если время не установлено

    const now = new Date();
    const diff = blinkEndTime - now;

    if (diff <= 0) return '00:00:00'; // Если время истекло

    const hours = Math.floor(diff / (1000 * 60 * 60));
    const minutes = Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((diff % (1000 * 60)) / 1000);

    return `${hours}:${minutes}:${seconds}`;
}

/**
 * Запускает таймер для обновления времени до срабатывания и времени мигания.
 * 
 * @param {Object} alarm - Объект будильника.
 * @returns {void}
 */
function startTimer(alarm) {
    const row = document.querySelector(`#alarmTable tbody tr:nth-child(${alarm.id})`);
    const timeUntilCell = row.querySelector('.time-until');
    const blinkTimeCell = row.querySelector('.blink-time');

    const timerInterval = setInterval(() => {
        const now = new Date();

        // Обновляем время до срабатывания
        const timeUntilAlarm = alarm.time - now;
        if (timeUntilAlarm <= 0) {
            timeUntilCell.textContent = '00:00:00';
        } else {
            timeUntilCell.textContent = formatTimeUntilAlarm(alarm.time);
        }

        // Обновляем время мигания
        if (alarm.blinkEndTime) {
            const blinkTimeLeft = alarm.blinkEndTime - now;
            if (blinkTimeLeft <= 0) {
                blinkTimeCell.textContent = '00:00:00';
            } else {
                blinkTimeCell.textContent = formatBlinkTime(alarm.blinkEndTime);
            }
        }
    }, 1000); // Обновляем каждую секунду
}
