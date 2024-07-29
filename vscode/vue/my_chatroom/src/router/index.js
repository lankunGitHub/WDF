import { createRouter, createWebHistory } from 'vue-router'
import Friend from '../components/Friend.vue'
import Group from '../components/Group.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {path: '/friend', component: Friend},
    {path: '/group', component: Group},
  ]
})

export default router
