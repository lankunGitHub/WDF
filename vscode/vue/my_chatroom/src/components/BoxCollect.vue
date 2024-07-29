<script setup>
//import { RouterLink, RouterView } from 'vue-router'
</script>

<template>
  <div class="box_collect">
    记事本
  </div>
</template>
  
<style scoped>
* {
  margin: 0;
  padding: 0;
  border: 0;
}

.box_collect {
  position: absolute;
  top: 80%;
  left: 2%;
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
</style>
