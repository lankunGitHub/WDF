<script setup>
//import { RouterLink, RouterView } from 'vue-router'
</script>

<template>
  <div>
    <button class="show_settings">我是按钮</button>
    <div class="box_settings">

    </div>
  </div>
</template>
  
<style scoped>
* {
  margin: 0;
  padding: 0;
  border: 0;
}

.box_settings {
  position: absolute;
  top: 3%;
  left: 70%;
  width: 25%;
  height: 5%;
  
  background-color: rgba(255, 255, 255, 0.5);
  /* 设置半透明的白色背景 */
  backdrop-filter: blur(10px);
  /* 使用背景滤镜实现模糊效果 */
  border-radius: 25px;
  /* 设置圆角 */
  padding: 20px;
  /* 设置内边距 */
}

.show_settings {
  position: absolute;
  top: 3%;
  left: 97%;
}
</style>
