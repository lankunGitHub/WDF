<script setup>
//import { RouterLink, RouterView } from 'vue-router'
import '@/assets/fonts/fonts.css'

import { ref } from 'vue'

import BoxCalander from '@/components/BoxCalander.vue'

let judge = ref(false)

let date = new Date()
let year = ref(0)
let day = ref(0)
let hours = ref(0)
let minutes = ref(0)
let seconds = ref(0)
let month = ref(0)
let am = ref('')
let week_index = ref(0)
const week_name =['Mon', 'Tes', 'Wes', 'Thu', 'Fri', 'Sat', 'Sun']
let week = ref('')

setInterval(() => {
  date = new Date();
  year.value = date.getFullYear();
  day.value = date.getDate();
  hours.value = String(date.getHours()).padStart(2, '0');
  minutes.value = String(date.getMinutes()).padStart(2, '0');
  seconds.value = String(date.getSeconds()).padStart(2, '0');
  month.value = date.getMonth() + 1;

  week_index = date.getDay() - 1
  week.value = week_name[week_index]
  am.value = hours.value < 12 ? 'AM' : 'PM';
}, 1000)

</script>

<template>
  <div class="box_time">
    <div class="time">{{ hours }} : {{ minutes }} : {{ seconds }} {{ am }}</div>
    <div class="date" @mouseenter="judge = true" @mouseleave="judge = false">&lt {{ year }}.{{ month }}.{{ day }} | {{ week }} >
      <BoxCalander v-show="judge" ></BoxCalander>
    </div>
    <div class="calendar"></div>
  </div>
</template>
  
<style scoped>
* {
  margin: 0;
  padding: 0;
  border: 0;
}

.box_time {
  position: absolute;
  top: 50%;
  left: 2%;
  width: 25%;
  height: 20%;

  background-color: rgba(255, 255, 255, 0.5);
  /* 设置半透明的白色背景 */
  backdrop-filter: blur(10px);
  /* 使用背景滤镜实现模糊效果 */
  border-radius: 25px;
  /* 设置圆角 */
  padding: 20px;
  /* 设置内边距 */
}

.time {
  position: absolute;
  top: 5%;
  left: 5%;
  width: 90%;
  height: 60%;

  font-family: AmaticSC-Bold;
  font-size: 5vw;
  text-align: center;
  line-height: 7vw;
  color: black;

  /* background-color: rgba(255, 255, 255, 0.5);
  backdrop-filter: blur(10px);
  border-radius: 25px;
  padding: 20px; */
}

.date {
  position: absolute;
  top: 70%;
  left: 5%;
  width: 90%;
  height: 30%;

  font-family: AmaticSC-Bold;
  font-size: 3vw;
  text-align: center;
  line-height: 3vw;
  color: black;
}

</style>
