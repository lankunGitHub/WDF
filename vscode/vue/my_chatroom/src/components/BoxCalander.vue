<template>
  <div class="calendar">
  <div class="calendar-header">
    <button @click="previousMonth">&lt;</button>
    <h2>{{ monthYear }}</h2>
    <button @click="nextMonth">&gt;</button>
  </div>
  <div class="calendar-grid">
    <!-- 显示星期几 -->
    <div class="calendar-day" v-for="dayOfWeek in weekdays" :key="dayOfWeek">{{ dayOfWeek }}</div>
    <!-- 显示日期 -->
    <div v-for="(_, i) in firstDay" :key="'empty-' + i" class="calendar-day empty"></div>
    <div v-for="day in totalDays" :key="day" :class="['calendar-day', { today: isToday(day) }]">
      <div>{{ day }}</div>
    </div>
  </div>
</div>
</template>

<script setup>
import { ref, computed } from 'vue';
import '@/assets/fonts/fonts.css'

const currentMonth = ref(new Date().getMonth());
const currentYear = ref(new Date().getFullYear());

const monthNames = [
  'January',
  'February',
  'March',
  'April',
  'May',
  'June',
  'July',
  'August',
  'September',
  'October',
  'November',
  'December',
];

const weekdays = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat']; // 添加星期数组

const monthYear = computed(() => `${monthNames[currentMonth.value]} ${currentYear.value}`);

const firstDay = computed(() => new Date(currentYear.value, currentMonth.value, 1).getDay());
const totalDays = computed(() => new Date(currentYear.value, currentMonth.value + 1, 0).getDate());

const isToday = (day) => {
  const today = new Date();
  return (
    day === today.getDate() &&
    currentMonth.value === today.getMonth() &&
    currentYear.value === today.getFullYear()
  );
};

const previousMonth = () => {
  currentMonth.value--;
  if (currentMonth.value < 0) {
    currentMonth.value = 11;
    currentYear.value--;
  }
};

const nextMonth = () => {
  currentMonth.value++;
  if (currentMonth.value > 11) {
    currentMonth.value = 0;
    currentYear.value++;
  }
};

const getDayOfWeek = (day) => {
  const date = new Date(currentYear.value, currentMonth.value, day);
  return weekdays[date.getDay()];
};
</script>

<style scoped>
.calendar {
  position: absolute;
  top: -950%;
  left: -7%;
  width: 110%;

  background-color: rgb(18, 165, 214);
  border: 1px solid #ccc;
  border-radius: 5px;
  padding: 5px;
  text-align: center;
  backdrop-filter: blur(10px);
  border-radius: 25px;
  padding: 10px;
  transform: scale(1);
  font-family: AmaticSC-Bold;
}

.calendar-header {

  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 10px;

}

.calendar-grid {
  display: grid;
  grid-template-columns: repeat(7, 1fr);
  gap: 3px;
}

.calendar-day {
  padding: 3px;
  border-radius: 3px;
}

.empty {
  background-color: transparent;
}

.today {
  font-weight: bold;
}

button {
  font-family: AmaticSC-Bold;
  font-size: 100%;
  background-color: transparent;
  border: none;
  outline: none;
}

</style>
