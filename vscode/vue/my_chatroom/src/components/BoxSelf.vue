<script setup>
//import { RouterLink, RouterView } from 'vue-router'

</script>

<template>
  <div class="box_self">
    <div class="self_image">

    </div>
    <div class="name">
      name
    </div>
    <div class="collect"></div>
  </div>
</template>
  
<style scoped>
* {
  margin: 0;
  padding: 0;
  border: 0;
}

.box_self {
  position: absolute;
  top: 30%;
  left: 35%;
  width: 30%;
  height: 40%;
  
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
  line-height: 20vw;
}

.self_image {
  position: absolute;
  top: 5%;
  left: 5%;
  width: 40%;
  height: 60%;

  background-color: rgba(255, 255, 255, 0.5);
  /* 设置半透明的白色背景 */
  backdrop-filter: blur(10px);
  /* 使用背景滤镜实现模糊效果 */
  border-radius: 25px;
  /* 设置圆角 */

  
}

.name {
  position: absolute;
  top: 5%;
  left: 50%;
  width: 40%;
  height: 60%;

  background-color: rgba(255, 255, 255, 0.5);
  /* 设置半透明的白色背景 */
  backdrop-filter: blur(10px);
  /* 使用背景滤镜实现模糊效果 */
  border-radius: 25px;
  /* 设置圆角 */

}

.collect {
  position: absolute;
  top: 75%;
  left: 5%;
  width: 90%;
  height: 20%;

  background-color: rgba(255, 255, 255, 0.5);
  /* 设置半透明的白色背景 */
  backdrop-filter: blur(10px);
  /* 使用背景滤镜实现模糊效果 */
  border-radius: 25px;
  /* 设置圆角 */

}
</style>
