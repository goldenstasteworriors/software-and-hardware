## engineai_legged_gym

夏天学长在legged_robot中做的更改:

1.  应用随机化的mass和com
2. command不归一化到-pi~pi范围
3. heading_command设为false
4. measure_heights从固定为0变为随机





heading:开了的话角速度取的当前朝向和目标朝向的差值，否则随机生成一个转向速度

更换GPU：export CUDA_VISIBLE_DEVICES=1

### 3_25

1. legged_robot.py中把config中非0的奖励scale全部读完，然后用

   ```
   name = '_reward_' + name
   self.reward_functions.append(getattr(self, name))
   ```

   调对应的奖励函数算出来相乘

2. 看sim2sim结果调参数，主要是hip的pd参数和奖励参数，要柔一些就调小一点刚度(刚度是使速度尽可能跟随的)，由于速度波动较大所以阻尼不要给太大；hip的roll是往外踢，yaw是扭转，pitch是往前踢；roll一般要给小，因为脚很容易侧着踩，如果刚度太大容易侧翻





