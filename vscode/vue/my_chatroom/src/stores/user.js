import { defineStore } from 'pinia'

export const Websocket = defineStore('socket', {
  state: () => {
    return {
      socket: 0,
      log: true
    }
  },
})