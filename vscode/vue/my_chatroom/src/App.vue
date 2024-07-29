<script setup>
//import { RouterLink, RouterView } from 'vue-router'
import { ref } from 'vue'
import '@/assets/fonts/fonts.css'

import { Websocket } from '@/stores/user'

import BoxLable from '@/components/BoxLable.vue'
import BoxTime from '@/components/BoxTime.vue'
import BoxSearch from '@/components/BoxSearch.vue'
import BoxCollect from '@/components/BoxCollect.vue'
import BoxSelf from '@/components/BoxSelf.vue'
import BoxApp from '@/components/BoxApp.vue'
import BoxSettings from '@/components/BoxSettings.vue'
import BoxWindow from '@/components/BoxWindow.vue'
import BoxWinChange from '@/components/BoxWinChange.vue'

//import { send } from 'vite'

const socket = new WebSocket("ws://10.30.0.197:8080");
Websocket.socket = socket
socket.onerror = function () {
  alert("无网络")
};

const token = sessionStorage.getItem('token');
const email = sessionStorage.getItem('email');
const password = sessionStorage.getItem('email');

let log = ref(false)

 if (token) {
  logobc.email.value = email
  logobc.password.value = password
  logenter()
 } 


//遮挡卡片
let islog = ref(true)
let issig = ref(false)
let login = ref('欢迎回来')
function movecover() {
  islog.value = !islog.value;
  issig.value = !issig.value;
  if (islog.value) {
    login.value = '欢迎回来'
  }
  else {
    login.value = '新用户'
  }
}



//登陆记录
let logobc = ref({
  type: 2,
  email: '',
  password: '',
  check: 'NULL',
})
//忘记密码
let forget = ref(false)

function showcheck() {
  if (!forget.value)
    forget.value = !forget.value

  logobc.password = '';

}

let sendcheckcode = ref({
  type: 35,
  address: '',
})

function getcheck() {
  if (logobc.value.email === '') {
    alert("邮箱不能为空")
    return;
  }
  sendcheckcode.value.address = logobc.value.email
  socket.send(JSON.stringify(sendcheckcode))
  alert('验证码已发送')
}
//登陆成功
function logenter() {
  发送登陆信息
  socket.send(JSON.stringify(logobc));
  //返回用户验证

  const timeoutId = setTimeout(() => {
    // 超时处理逻辑
    alert('请求超时，请稍后再试');
  }, 20000);

  socket.onmessage = function (event) {
    clearTimeout(timeoutId);
    let retcheck = JSON.parse(event.data)
    if (retcheck.name === '') {
      alert('用户不存在')
      logobc.value.email = ''
      logobc.value.password = ''
      return;
    }
    if (forget.value === true && retcheck.checkcode === 'FALSE') {
      alert("验证码错误")
      logobc.value.email = ''
      logobc.value.password = ''
      return;
    }
    if (forget.value === false && retcheck.password === '') {
      alert('密码错误')
      logobc.value.email = ''
      logobc.value.password = ''
      return;
    }
    alert(`欢迎用户：${retcheck.name}`)
    sessionStorage.setItem('token', retcheck.token);
    sessionStorage.setItem('email', retcheck.email);
    sessionStorage.setItem('password', retcheck.password);
  log.value = !log.value
   };
}



//注册记录
let sigobc = ref({
  type: 0,
  email: '',
  password: '',
  check: '',
})

function getcheck1() {
  if (sigobc.value.email === '') {
    alert("邮箱不能为空")
    return;
  }
  sendcheckcode.value.address = sigobc.value.email
  socket.send(JSON.stringify(sendcheckcode))
  alert('验证码已发送')
}

//注册成功
function sigenter() {
  //发送登陆信息
  socket.send(JSON.stringify(sigobc));

  const timeoutId = setTimeout(() => {
    // 超时处理逻辑
    alert('请求超时，请稍后再试');
  }, 20000);

  //返回用户验证
  socket.onmessage = function (event) {
    clearTimeout(timeoutId);
    let retcheck = JSON.parse(event.data)
    if (retcheck.check === '-1') {
      alert("验证码错误，请重试")
      return;
    }

    sessionStorage.setItem('token', retcheck.token);
    sessionStorage.setItem('email', retcheck.email);
    sessionStorage.setItem('password', retcheck.password);

    log.value = !log.value
  }
}

</script>
  
<template>
  <div class="back" v-if="log">
    <div v-if="log" class="wappear">
      <div class="login">
        <h1 style="text-align: center;">登录</h1>
        <form action="">
          <div class="login_content">
            <input type="text" v-model="logobc.email" class="acount" placeholder="邮箱"> <br>
            <input type="password" v-model="logobc.password" class="password" placeholder="密码" v-if="!forget"> <br>
            <input type="password" v-model="logobc.password" class="password" placeholder="新密码" v-if="forget"> <br>
            <a v-if="!forget" class="forget" @click="showcheck">忘记密码</a>
            <a v-if="forget" class="forget1" @click="getcheck">获得验证码</a>
            <div v-if="forget">
              <input type="text" placeholder="验证码" class="checkcode" v-model="logobc.check">
            </div>
          </div>
          <button type="submit" class="submit" @click="logenter">登录</button>
        </form>
      </div>
      <div class="signin">
        <h1 style="text-align: center;">注册</h1>
        <form action="">
          <div class="login_content">
            <input type="text" v-model="sigobc.email" class="acount" placeholder="邮箱"> <br>
            <input type="password" v-model="sigobc.password" class="password" placeholder="密码"> <br>
            <div>
              <input type="text" placeholder="验证码" class="checkcode" v-model="sigobc.check">
              <a class="forget1" @click="getcheck1">获得验证码</a>
            </div>
          </div>
          <button type="submit" class="submit" @click="sigenter">注册</button>
        </form>
      </div>
      <div :class="{ coversig: islog, coverlog: issig }" @click="movecover" class="cover_font">{{ login }}</div>
    </div>
  </div>

  <div class="back" v-else>
    <BoxLable></BoxLable>
    <BoxTime></BoxTime>
    <BoxSearch></BoxSearch>
    <BoxCollect></BoxCollect>
    <BoxSelf></BoxSelf>
    <BoxApp></BoxApp>
    <BoxSettings></BoxSettings>
    <BoxWindow></BoxWindow>
    <BoxWinChange></BoxWinChange>
  </div>
</template>
  
<style scoped>
* {
  margin: 0;
  padding: 0;
  border: 0;
}


body,
html {
  margin: 0;
  padding: 0;
  border: 0;
}

.back {
  background-image: url(./assets//image/1330715.png);
  background-size: cover;
  /* 让背景图片填满整个屏幕 */
  background-position: center;
  /* 将背景图片居中 */
  height: 100vh
}

.wappear {
  position: absolute;
  top: 15%;
  left: 25%;
  width: 50%;
  height: 60%;

  background-color: rgba(255, 255, 255, 0.5);
  /* 设置半透明的白色背景 */
  backdrop-filter: blur(10px);
  /* 使用背景滤镜实现模糊效果 */
  border-radius: 25px;
  /* 设置圆角 */
  padding: 20px;
  /* 设置内边距 */

  transition: transform 0.5s ease;
}

.login {
  position: absolute;
  top: 0%;
  left: 0%;
  width: 50%;
  height: 100%;

}

.signin {
  position: absolute;
  top: 0%;
  left: 50%;
  width: 50%;
  height: 100%;

}

.coversig {
  position: absolute;
  top: 0%;
  left: 50%;
  width: 50%;
  height: 100%;

  background-color: blue;
  transition: left 0.5s ease;
  cursor: pointer;

  z-index: 1;
}

.coverlog {
  position: absolute;
  top: 0%;
  left: 0%;
  width: 50%;
  height: 100%;

  background-color: blue;
  transition: left 0.5s ease;
  cursor: pointer;

  z-index: 1;
}

.cover_font {
  font-size: 500%;
  text-align: center;
  line-height: 1000%;
  color: aliceblue;

  font-family: AmaticSC-Bold;
}

.login_content {
  position: absolute;
  top: 10%;
  left: 10%;
  width: 80%;
  height: 70%;

}

.acount {
  position: absolute;
  top: 30%;
  left: 20%;
  width: 60%;
  height: 7%;

  font-size: 200%;
  color: black;

  border: none;
  border-bottom: 1px solid black;
  background-color: transparent;
  outline: none;

}

.password {
  position: absolute;
  top: 50%;
  left: 20%;
  width: 60%;
  height: 7%;

  font-size: 200%;

  border: none;
  border-bottom: 1px solid black;
  background-color: transparent;
  outline: none;
}

.forget {
  position: absolute;
  top: 60%;
  left: 40%;

  color: blue;
  font-size: large;

  border: none;
  border-bottom: 1px solid black;
  background-color: transparent;
  outline: none;
  cursor: pointer;
}

.checkcode {
  position: absolute;
  top: 70%;
  left: 20%;
  width: 60%;
  height: 7%;

  font-size: 200%;

  border: none;
  border-bottom: 1px solid black;
  background-color: transparent;
  outline: none;

}

.submit {
  position: absolute;
  top: 80%;
  left: 40%;
  width: 20%;
  height: 7%;

  font-size: large;
  border-radius: 25px;
  background-color: rgb(242, 118, 138)
}

.forget1 {
  position: absolute;
  top: 80%;
  left: 40%;

  color: blue;
  font-size: large;

  border: none;
  border-bottom: 1px solid black;
  background-color: transparent;
  outline: none;

  cursor: pointer;
}
</style>
