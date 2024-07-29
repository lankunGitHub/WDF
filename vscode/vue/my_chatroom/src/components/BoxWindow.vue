<script setup>
import { RouterLink, RouterView } from 'vue-router'
</script>

<template>
  <div class="box_window">
    <div class="leader_bar" >
      <button class="back_button">退后</button>
      <router-link to="/friend" class="friend">好友</router-link>
      <router-link to="/group" class="group">群聊</router-link>
      <button class="add_button">添加</button>
      
    </div>
    <router-view class="show_content"></router-view>
  </div>
</template>
  
<style scoped>
  * {
    margin: 0;
    padding: 0;
    border: 0;
  }
  
  .box_window {
  position: absolute;
  top: 15%;
  left: 70%;
  width: 25%;
  height: 80%;
  
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
  line-height: 35vw;
}

.leader_bar{
  position: absolute;
  top: 1%;
  left: 1%;
  width: 98%;
  height: 10%;

}

.show_content{
  position: absolute;
  top: 12%;
  left: 1%;
  width: 98%;
  height: 87%;
}

.back_button{
  position: absolute;
  top: 10%;
  left: 5%;
}

.add_button{
  position: absolute;
  top: 10%;
  right: 5%;
}

.friend{
  position: absolute;
  top: 10%;
  left: 31%;
  width: 20%;
  height: 60%;

  text-align: center;
  line-height: 200%;
  font-size: 50%;
  text-decoration: none;
  color: black;

  background-color: aqua;
  border-top-left-radius: 25px;
  border-bottom-left-radius: 25px;
}

.group{
  position: absolute;
  top: 10%;
  right: 31%;
  width: 20%;
  height: 60%;
  border-top-right-radius: 25px;
  border-bottom-right-radius: 25px;

  text-align: center;
  line-height: 200%;
  font-size: 50%;
  text-decoration: none;
  color: black;

  background-color: beige;
}


</style>
