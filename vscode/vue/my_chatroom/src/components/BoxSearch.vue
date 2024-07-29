<script setup>
//import { RouterLink, RouterView } from 'vue-router'
import '@/assets/fonts/fonts.css'

let search_content = ''

function commit() {
  console.log(search_content)
  let search_ = "https://www.google.com/search?q=" + encodeURIComponent(search_content);
  window.open(search_)
}

</script>

<template>
  <div class="box_sreach">
    <input type="search" class="input_sty" placeholder="s r e a c h" v-model="search_content" @keydown.enter="commit">
    <label class="labels">Input content</label>
    <div class="top_line"></div>
  </div>
</template>
  
<style scoped>
* {
  margin: 0;
  padding: 0;
  border: 0;
}

.box_sreach {
  position: absolute;
  top: 10%;
  left: 35%;
  width: 25%;
  height: 10%;

  background-color: rgba(255, 255, 255, 0.5);
  /* 设置半透明的白色背景 */
  backdrop-filter: blur(10px);
  /* 使用背景滤镜实现模糊效果 */
  border-radius: 25px;
  /* 设置圆角 */
  padding: 20px;
  /* 设置内边距 */

  font-size: 3vw;
  text-align: center;
  line-height: 5vw;
}

.input_sty {
  position: absolute;
  top: 30%;
  left: 5%;
  width: 90%;
  height: 40%;
  background: transparent;
  border: 2px solid #0B2447;
  border-top: none;
  outline: none;
  box-shadow: 7px 7px 0px 0px #0B2447;
  transition: all 0.5s;

  font-size: 40%;
  font-family: longzangti;
  /* text-shadow: 3px 3px 2px rgba(5, 5, 5, 0.5) */
}

.input_sty:focus {
  box-shadow: none;
  transition: all 0.5s;
}

.top_line {
  position: absolute;
  top: 30%;
  right: 5%;
  height: 2px;
  width: 90%;
  background-color: #0B2447;
  transition: all 0.5s;
}

.box_sreach input[type="search"]:focus~.top_line {
  width: 45%;
  transition: all 0.5s;
}

.labels {
  position: absolute;
  top: -10%;
  left: 6%;
  color: #0B2447;
  transition: all 0.5s;
  transform: scale(0);
  z-index: -1;
  opacity: 0.6;
  font-size: 40%;
  font-family: longzangti;
}

.box_sreach input[type="search"]:focus~.labels {
  top: -15%;
  left: 10%;
  transform: scale(1);
  transition: all 0.5s;
}
</style>
