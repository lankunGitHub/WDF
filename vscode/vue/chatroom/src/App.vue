<script setup>
//import { RouterLink, RouterView } from 'vue-router'
import { ref, computed } from 'vue'

//用户
let user = ref({
  user_id: "-1",
  email: "",
  name: "",
  avatar_url: "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_960_720.png",  //默认头像
  token: "",
  pack_id: "0",
})
//文件字典
let file_dictionary = {};
let file_dictionary_all = {
  auther: "",
  title: "",
  finish: false,
  file_id: "",
};
function file_prase(data) {
  
}

//好友列表
let friend_list = ref([
  {
    friend_id: "0",
    name: "小助手",
    friend_avatar_url: "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_960_720.png",  //默认头像
    type: "1",
    pack_id: "0"
  }
]);

//客户端操作
function enterClinet(messageobj) {
  user.value.user_id = messageobj.user_id;
  user.value.name = messageobj.name;
  user.value.email = messageobj.email;
  user.value.avatar_url = messageobj.avatar_url;
  user.value.token = messageobj.token;
  user.value.pack_id = messageobj.pack_id;
  console.log(user.value);
  log.value = !log.value;
}

function addFriendList(messageobj) {
  friend_list.value.push({
    friend_id: messageobj.friend_id,
    name: messageobj.name,
    friend_avatar_url: messageobj.friend_avatar_url,
    type: messageobj.type,
    pack_id: messageobj.pack_id,
  })
}

// 创建websocket连接
const socket = new WebSocket("ws://10.30.0.205:8080");
//连接失败
socket.onerror = function () 
{
  console.error('WebSocket connection error:', event);
  alert("服务器连接失败，请重试！");
};

//连接成功
socket.onopen = function () {
  console.log('WebSocket connection open');
};

// socket.onclose = function ()
// {
//   alert("服务器断开");
// }
//接收到消息后
socket.onmessage = function (event) {
  let message = event.data;
  if (event.data instanceof ArrayBuffer) {
    let pack = {
      content: "",
      pack_id: "",
      end: false,
    };
    pack = file_prase(message);
    if (file_dictionary.hasOwnProperty(pack.pack_id)) {
      file_dictionary[pack.pack_id] += pack.content;
    } else {
      file_dictionary[pack.pack_id] = pack.content;
    }
    if (pack.end) { 
      file_dictionary_all[pack.pack_id].finish = true;
    }
  }
  else {
    console.log(message);
    let messageobj = JSON.parse(message);
    switch (message.type) {
      case -1: //验证码错误
        alert("验证码错误！请重试");
        break;
      case -2: //用户已存在
        alert("用户已存在");
        break;
      case -3: //邮箱或密码错误
        alert("邮箱或密码错误");
        break;
      case 0:
        alert("服务失败，请重试");
        break;
      case 1:
        enterClinet(messageobj);
      case 2:
        addFriendList(messageobj);
    }
  }
}

//如果忘记密码登陆方式
let forget = ref(false);
function changeforget() { forget.value = !forget.value; }

//登录覆盖
let coverlog = ref(0);
let logmind = ref("Click me to sign up");
function changecoverlog() {
  if (coverlog.value === 0) {
    logmind.value = "Click me to login";
    coverlog.value = -704;
  }
  else {
    logmind.value = "Click me to sign up";
    coverlog.value = 0;
  }
}

//发送验证码
function sendcode() {
  if (user.value.email === "") {
    alert("请先输入邮箱！");
    return;
  }
  if (user.value.password === "") {
    alert("请先输入新密码！");
    return;
  }
  const timestamp = new Date().getTime();
  socket.send(JSON.stringify({
    type: "4",
    email: user.value.email,
    time: timestamp,
  }));
  alert("验证码以发送到邮箱，有效时间为5分钟，请注意查收！");
}

let log = ref(true);

//登录注册进入
function changelog() {
  user.value.name = "User_" + user.value.email
  log.value = !log.value;
  if (coverlog.value === 0)  //登录
  {
    if (forget.value === true) {
      socket.send(JSON.stringify({
        type: "3",
        email: user.value.email,
        password: user.value.password,
        code: user.value.code,
        name: user.value.email,
        avatar_url: "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_960_720.png",
        user_id: user.value.user_id,
        token: user.value.token,
      }))
    }
    else {
      console.log(JSON.stringify({
        type: "2",
        email: user.value.email,
        password: user.value.password,
        name: user.value.email,
        avatar_url: "default",
        user_id: user.value.user_id,
        token: user.value.token,
      }))
      socket.send(JSON.stringify({
        type: "2",
        email: user.value.email,
        password: user.value.password,
        name: user.value.email,
        avatar_url: "default",
        user_id: user.value.user_id,
        token: user.value.token,
      }))
    }
  }
  else if (coverlog.value === -704)  //注册
  {
    socket.send(JSON.stringify({
      type: "0",
      email: user.value.email,
      password: user.value.password,
      code: user.value.code,
      name: "无名氏",
      avatar_url: "default",
      user_id: user.value.user_id,
      token: user.value.token,
    }))
    console.log("发送")
  }
};

//进入页面
let setting = ref(false);
let settingwindow = ref(false);
function changesetting() {
  setting.value = !setting.value;
}

function getURL(pack_id) {
  if (pack_id === "-1") {
    return null;
  }
  else if (pack_id === "0") {
    return "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_960_720.png";
  }
  else {
    let filedata = new Blob([file_dictionary[pack_id]], { type: "application/octet-stream" });
    return URL.createObjectURL(filedata);
  }
}

function LogOut() {
  log.value = !log.value;
  setting.value = !setting.value;
  user.value.user_id = "-1";
  user.value.email = "";
  user.value.name = "";
  user.value.avatar_url = "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_960_720.png";
  user.value.token = "";
  user.value.pack_id = "0";
  user.value.password = "";
  socket.send(JSON.stringify({
    type: "1",
    user_id: user.value.user_id,
  }))
}
</script>

<template>
  <div class="wapper">

    <div class="log" v-if="log">
      <div style="display: flex; flex-direction: column; justify-content: center; align-items: center; margin: 50px;">
        <h1 style="font-size: 70px;">Welcome To</h1>
        <h1 style="font-size: 70px;">My Chatroom</h1>
        <p class="typing" style="margin: 20px; font-size: 50px;">All Tragedy Erased, I See Only Wonders</p>
      </div>
      <div class="logform">
        <h1>登录</h1>
        <input type="text" class="loginput" placeholder="  邮 箱" v-model="user.email">
        <input type="password" class="loginput" placeholder="  密 码" v-if="!forget" v-model="user.password">
        <input type="password" class="loginput" placeholder="  新 密 码" v-if="forget" v-model="user.password">
        <input type="text" class="loginput" placeholder="  验 证 码" v-if="forget" v-model="user.code">
        <a v-if="!forget" @click.prevent="changeforget" class="aforget">忘记密码</a>
        <a v-if="forget" class="aforget" @click.prevent="sendcode">获得验证码</a>
        <button @click.prevent="changelog">登录</button>
      </div>
      <div class="logform">
        <h1>注册</h1>
        <div class="coverlog" :style="{ transform: 'translateX(' + coverlog + 'px)' }" @click="changecoverlog">
          {{ logmind }}
        </div>
        <input type="text" class="loginput" placeholder="  邮 箱" v-model="user.email">
        <input type="password" class="loginput" placeholder="  新 密 码" v-model="user.password">
        <input type="text" class="loginput" placeholder="  验 证 码" v-model="user.code">
        <a class="aforget" @click.prevent="sendcode">获得验证码</a>
        <button @click.prevent="changelog">注册</button>
      </div>
    </div>

    <div class="interface" v-if="!log">

      <div class="left_list">
        <div class="person_setting">
          <div class="person">
            <img :src="getURL(user.pack_id)" class="avatar">
            <div>
              <p style="font-size: 30px;">{{ user.name }}</p>
              <p style="font-size: 30px;">{{ user.email }}</p>
            </div>
          </div>
          <div class="setting">
            <img src="./assets/img/icons8-单选.gif" style="width: 70px; height: 70px;" @click="changesetting">
            <div class="setting_list" v-show="setting">
              <div class="setting_choice">修改个人信息</div>
              <div class="setting_choice">添加好友或群聊</div>
              <div class="setting_choice">创建群聊</div>
              <div class="setting_choice" @click.prevent="LogOut">注销</div>
            </div>
          </div>
        </div>
        <div class="friend_list" v-for="item in friend_list" :key="item.friend_id">
          <img :src="getURL(item.pack_id)" class="avatar">
          <p>{{ item.name }}</p>
        </div>
        <div></div>
      </div>
      <div class="settingwindow" v-show="settingwindow">

      </div>
      <div class="chatwindow">

      </div>
    </div>
  </div>
</template>

<style scoped>
.wapper {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  height: 100vh;
  width: 100vw;
  background-image: url(./assets/img/svg.png);
  background-size: cover;
  background-repeat: no-repeat;
}

button {
  width: 150px;
  height: 80px;
  border-radius: 50px;
  border: none;
  background-color: rgb(175, 175, 237);
  font-size: 25px;
  color: rgb(255, 255, 255);

  margin: 50px;
}

.log {
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-items: center;
}

.logform {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  width: 700px;
  height: 900px;
  background-color: rgb(255, 255, 255);
  border-radius: 25px;
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.5);
  margin: 2px;
}

.loginput {
  width: 500px;
  height: 80px;
  border-radius: 25px;
  border: 5px solid #afafed;
  margin: 30px;

  font-size: 25px;
}

.aforget {
  cursor: pointer;
  font-size: 20px;
}

.aforget:hover {
  color: rgb(175, 175, 237);
  text-decoration: underline;
}

.coverlog {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  position: absolute;
  margin: 2px;
  width: 700px;
  height: 900px;
  border-radius: 25px;
  background-color: #afafed;
  background-size: cover;
  background-repeat: no-repeat;
  z-index: 1;
  transition: transform 0.5s ease;

  font-size: 50px;
}

.typing {
  width: 16.5em;
  height: 1.25em;
  border-right: 1px solid transparent;
  animation: typing 3s steps(35, end), blink-caret .75s step-end;
  font-family: Consolas, Monaco;
  word-break: break-all;
  overflow: hidden;
}

/* 打印效果 */
@keyframes typing {
  from {
    width: 0;
  }

  to {
    width: 16.5em;
  }
}

/* 光标闪啊闪 */
@keyframes blink-caret {

  from,
  to {
    border-color: transparent;
  }

  50% {
    border-color: currentColor;
  }
}

/* 聊天 */
.interface {
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  align-items: center;
  width: 100vw;
  height: 100vh;
  background-color: rgb(237, 235, 235);
  border-radius: 25px;
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.5);
  margin: 2px;
}

.left_list {
  display: flex;
  flex-direction: column;
  justify-content: flex-start;
  align-items: center;
  width: 500px;
  height: 100vh;
  background-color: rgb(255, 255, 255);
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.5);
  margin: 2px;
}

.person_setting {
  display: flex;
  width: 100%;
  flex-direction: row;
  align-items: center;
  justify-content: space-between;
  flex-wrap: nowrap;

  border-bottom: 5px groove;
}

.avatar {
  display: flex;
  width: 150px;
  border-radius: 50%;
  object-fit: cover;
  margin-right: 40px;
}

.person {
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: space-between;
  flex-wrap: nowrap;
  margin: 20px;
}

.setting {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  margin: 30px;
}

.setting:hover {
  cursor: pointer;
}

.setting_list {
  position: absolute;
  top: 150px;
  left: 200px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  width: 350px;
  height: 320px;
  background-color: rgb(255, 255, 255);
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.5);
  margin: 2px;
  border-radius: 25px;
  transition: transform 0.5s ease;

  z-index: 1;
}

.setting_choice {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  width: 350px;
  height: 80px;
  border-bottom: 5px groove;

  font-size: 25px;
}

.setting_choice:last-child {
  border-bottom: none;
}

.setting_choice:hover {
  background-color: rgb(237, 235, 235);
}
</style>
