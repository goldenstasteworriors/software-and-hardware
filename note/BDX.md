### BDX

看一下什么硬件能部署模型

查看占用6006端口的进程lsof -i:6006

更换GPU：export CUDA_VISIBLE_DEVICES=4

批量关闭端口进程：for port in $(seq 6006 6025); do pid=$(lsof -t -i:${port}); if [ -n "$pid" ]; then kill -9 $pid && echo "Killed process on port $port (PID: $pid)"; fi; done

获取跑在GPU0上的含awd的进程：`ps aux | grep awd | grep -f <(nvidia-smi pmon -c 1 | grep ' 0 ' | awk '{print $2}')`

删除所有awd进程：`ps aux | grep '[a]wd' | awk '{print $2}' | xargs kill -9`

获取存储情况`du -h --max-depth=1 | sort -h`     `df -hl`

不看错误信息：在后面加 2>/dev/null，如`find / -name "libpython3.8.so.1.0" 2>/dev/null`

ljzzy@beibei

dhy



tensorboard --logdir /data5/ykj/output/stand_6_disc0/Duckling_19-08-54-34 --port 6008

2885626:4e-6 早

2885916:1e-5 晚



使用vscode上不了服务器而其他方法能上可以：`rm -rf ~/.vscode-server`

export LD_LIBRARY_PATH=/environment/miniconda3/envs/rlgpu/lib:$LD_LIBRARY_PATH

isaac gym:

```
# unzip files to a folder, then install with pip:
tar -xzvf IsaacGym_Preview_4_Package.tar.gz
cd isaacgym/python && pip install -e .
# check it is correctly installed by playing:
cd examples && python 1080_balls_of_solitude.py
```

















import torch
print(torch.cuda.is_available())  # 应该返回 True
print(torch.cuda.device_count())  # 应该返回 GPU 的数量



==19-22-08-46 my_bdx_backward/4e-6==

19/22:11 mini_bdx/4e-7



nohup python awd/run.py --task  DucklingCommand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_command_2.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6.yaml  --motion_file awd/data/motions/mini_bdx_all_60fps --headless > log/10900_2.log 2>&1 &







/home/yekangjie/Downloads/garbage/yolov5-autodl/classify/yolov5x-cls.pt



nohup python awd/run.py --resume 1 --task DucklingCommand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_command.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6.yaml --motion_file awd/data/motions/mini_bdx_all_60fps --checkpoint  /data6/ykj/output/10900.pth --output_path /data6/ykj/output/command_show_reward  --headless > log/command_show_reward.log 2>&1 &



==stand==

python awd/run.py  --task DucklingStand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_stand_4.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps  --output_path output/test --headless 



nohup  python awd/run.py --resume 1  --task DucklingStand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_stand_5.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps  --output_path output/test --checkpoint /data6/ykj/output/3_27/stand_5_disc0_standstill0.05_3/Duckling_27-08-54-54/nn/Duckling_00025000.pth --headless > log/stand_show_reward.log 2>&1 &





nohup python awd/run.py  --task DucklingStand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_stand_3.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps  --output_path output/stand_3_with_new_reward --headless  > log/stand_3_with_new_reward.log 2>&1 &



nohup python awd/run.py  --resume 1 --task DucklingCommand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_command.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6.yaml --motion_file awd/data/motions/mini_bdx_all_60fps --checkpoint /data5/ykj/output/10900_3_2days.pth --output_path /data5/ykj/output/3_27_109000_3_track_vel --headless > log/_27_109000_3_track_vel.log 2>&1 &



==bi_jump:==

nohup python awd/run.py   --task DucklingBiJump --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_bi_jump_extreme.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps --output_path  /data6/ykj/output/4_2/bi_jump_extreme/ --headless > log/extreme_bi_jump.log 2>&1 &

==trans==

nohup python awd/run.py   --task Trans --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/trans.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps --output_path  /data6/ykj/output/4_3/trans/ --headless > log/trans.log 2>&1 &



==测试==：

python awd/run.py  --test  --task DucklingCommand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_command.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6.yaml --motion_file awd/data/motions/mini_bdx_all_60fps --checkpoint weight/stand_by_accident/standstill350.pth



python awd/run.py  --test --task DucklingStand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_stand_4.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps --checkpoint weight/Duckling_6_0.pth



python awd/run.py --test --task DucklingStand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_stand_5.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps/ --checkpoint  weight.pth --headless





18-23-51-09 4e-6

19-23-35-47 1e-6

9-23-43-19 3e-6

19-23-44-30 2e-6

19-23-53-21 5e-6

19-23-53-34 7e-6

19-23-53-47 9e-6

20-00-05-12 2e-7

19-22-11-23 4e-7

20-00-06-57 4e-3_lin

20-00-10-44 4e-8

21-18-48-04 4e-6_mybdxbackaway_2

21-19-37-08 4e-6_minibdx_2

21-23-48-56 4e-6_minibdx_all_60fps

22-12-52-30 mybdxbackaway_3

22-17-16-51 4e-6_minibdx_all_60fps_plane_60hz

22-10-29-45 4e-6_minibdx_all_30fps

22-17-18-33 4e-6_minibdx_all_60fps_plane



23-18-27-02     4e-6_minibdx_all_60fps_plane_2

23-18-28-34     4e-6_minibdx_all_30fps_3

23-18-41-37    my_bdx_backward_4

23-18-55-42   4e-6_minibdx_all_60fps_3

23-18-51-08    4e-6_minibdx_3



26-00-20-02    10900_3

26-00-27-46     4e-6_minibdx_all_60fps_best_3

















mini_bdx

nohup python awd/run.py --task DucklingCommand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_command_plane.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task.yaml --motion_file awd/data/motions/my_bdx_backward --checkpoint /home/yekangjie/Downloads/AWD-main/output/Duckling_19-22-08-46/nn/Duckling_new.pth --headless &



python awd/run.py --test --task DucklingCommand --num_envs 128 --cfg_env /home/yekangjie/Downloads/AWD-main/awd/data/cfg/mini_bdx/duckling_command.yaml --cfg_train /home/yekangjie/Downloads/AWD-main/awd/data/cfg/mini_bdx/train/amp_duckling_task.yaml --motion_file /home/yekangjie/Downloads/AWD-main/awd/data/motions/mini_bdx/ --checkpoint /home/yekangjie/Downloads/AWD-main/output/Duckling_00038500.pth --headless







python3 auto_gait_generator.py -o gait_1_03_0_10 -n 1  --mini --min_dx -0.3 --max_dx 0.3 --min_dy 0 --max_dy 0 --length 10

# Isaac Gym

1. create sim时需要 

   ```python
   def create_sim(self):
       # implement sim set up and environment creation here
       #    - set up-axis(选择y轴朝上还是z轴朝上，并给重力)
       #如:          sim_params.up_axis = gymapi.UP_AXIS_Z
   	#	          sim_params.gravity = gymapi.Vec3(0.0, 0.0, -9.8)
       #    - call super().create_sim with device args (see docstring)
       #    - create ground plane
       #    - set up environments
   ```

   

2. gym里的tensor和pytorch里的不一样，要用pytorch的需要`gymtorch.wraptensor`转换，反之则`gymtorch.unwraptensor`

3. 每次调用`gym.simulate`都会推进一个仿真step，而这个step可以分成几个substep()





### 第二周 

#### 算法

AWD：鸭子版ASE，训练可重用的技能供下游任务调用

AMP：不从头训练而是先用大量数据生成一个style reward，然后后面只需要使用速度等简单reward和这个style reward相结合来训练

#### sim2real

![image-20241029224323129](../../pictrue/image-20241029224323129.png)

![image-20241029225242240](../../pictrue/image-20241029225242240.png)

```python
    class sim:
        dt = 0.005 %仿真时间间隔
        substeps = 1
        gravity = [0., 0., -9.81]  # [m/s^2]
        up_axis = 1  # 0 is y, 1 is z

        class physx:
            num_threads = 10
            solver_type = 1  # 0: pgs, 1: tgs
            num_position_iterations = 4
            num_velocity_iterations = 0
            contact_offset = 0.01  # [m]
            rest_offset = 0.0  # [m]
            bounce_threshold_velocity = 0.5  # 0.5 [m/s]
            max_depenetration_velocity = 1.0
            max_gpu_contact_pairs = 2 ** 23  # 2**24 -> needed for 8000 envs and more
            default_buffer_size_multiplier = 5
            contact_collection = 2  # 0: never, 1: last sub-step, 2: all sub-steps (default=2)

```



```python
    #             10, 'knee': 10, 'ankle': 10}  关节名字可以区分，mujoco下与其一致
    class control( LeggedRobotCfg.control ):
        # PD Drive parameters:
        control_type = 'P'
        stiffness = {'joint': 10.0}  # [N*m/rad]
        damping = {'joint': 0.4}     # [N*m*s/rad]
        # action scale: target angle = actionScale * action + defaultAngle
        action_scale = 0.3
        # decimation: Number of control action updates @ sim DT per policy DT
        decimation = 4
        hip_scale_reduction = 1

        use_filter = True
```



这里的：1/(decimation*dt)=50Hz

实时性：

UDP



##### miniBDX

用Raspberry Pi zero 2W的CPU跑，30Hz





runtime：

1. io_330:调接口给xl_330作通讯初始化并给常用功能包了一层
2. hwi：给io_330又包了一层并给了硬件连接口(usb)
3. onnx_infer：推理
3. rl_utils：各种工具



scripts：

1. GUSGUS:舵机正弦驱动
2. bench:测试性能(各个操作的时间)
3. commands_client：接收服务器的命令
4. control_server：确定使用控制器类型；作为服务器把接收到的控制器指令转发给客户端
5. rl_walk：获取obs，得到action(rma，输入融合根据最近历史信息得到的输入以修正?)
6. squat：给关节正弦输入偏差观察响应

##### Tinker(legged gym框架)

jetson nano边缘计算，200Hz





### 第三周

 1）弄清 state 的定义和参考系 2）弄清输出的定义 3）弄清怎么将参考轨迹或者参考速度输入到网络中

state：只需要获取root的[3:7], 线速度, 角速度，绝对参考系

推理的输出是相对于初始位置的舵机角度







reset/terminate:关节干涉/低于一定高度(摔倒？)，contact(摔倒)

每次调用post_physics_step时计算reward，检测是否reset/terminate,计算一次observer

duckling.py每一步reward恒定,duckling_heading

command:速度偏差+力矩偏差(力矩怎么测得？)



command初始化是0且只在reset_task和update_task中更新

update_command只在pre_physics_step中调用，即在每一step更新

z/s:x取最大/最小 d/q:y取最大/最小 a/e:角速度取最大/最小



在仿真中采取动作是通过a2c下的play_steps

获取root,dof等状态是靠gym.acquire_actor_root_state_tensor

root_state包含位置[0:3], 旋转[3:7], 线速度[7:10], 角速度[10:13]

quat_rotate_inverse(a,b)：b相对a旋转



### runtime：

obs：重力投影；命令；上一动作；上一命令的x,y速度及角速度*对应scale

开rma就结合历史obs推理，否则就直接用obs推理

推理得到action，舵机输出action+初始角度



### 第四周

步态生成：

placo参数固定：

在 `auto_gait_generator.py` 文件中，步态生成是通过多个参数来控制机器人的行走方式。这些参数包括机器人的步态长度、转弯角度、足部高度等。以下是主要的步态参数及其作用：

输入值控制dx,dy,dtheta；由步态生成器给出轨迹，vel_x,vel_y和yaw是算出来的

 	“dx/dy”：每个motion中随机，移动距离

​	“theta”：每个motion中随机，旋转角

​	"duration": 10,

​    "hardware": true,

​    "double_support_ratio": 0.20000,

​    "startend_double_support_ratio": 1.50000,

​    "planned_timesteps": 48,

​    "replan_timesteps": 10,

​    "walk_com_height": 0.16000,

​    "walk_foot_height": 0.03000,

​    "walk_trunk_pitch": -5.00000,

​    "walk_foot_rise_ratio": 0.20000,

​    "single_support_duration": 0.18000,双足支撑阶段的比例，越大越稳越慢

​    "single_support_timesteps": 10,

​    "foot_length": 0.06000,

​    "feet_spacing": 0.14000,

​    "zmp_margin": 0.00000,

​    "foot_zmp_target_x": 0.00000,

​    "foot_zmp_target_y": 0.00000,

​    "walk_max_dtheta": 1.00000,

​    "walk_max_dy": 0.10000,

​    "walk_max_dx_forward": 0.08000,

​    "walk_max_dx_backward": 0.03000

### 1. **dx (前进/后退距离)**
### 2. **dy (左右平移距离)**
### 3. **dtheta (转角)**
### 4. **length (步态持续的时间)**
### 5. **skip_warmup (跳过热身阶段)**
### 6. **stand (站立模式)**
### 7. **hardware (是否启用硬件)**
### 8. **debug (调试模式)**
### 9. **mini (是否使用迷你版机器人)**
### 10. **period (步态周期)**。
### 11. **double_support_ratio (双支撑阶段的比例)**
### 12. **startend_double_support_ratio (起始和结束的双支撑比例)**
### 13. **single_support_duration (单支撑阶段的持续时间)**
### 14. **foot_zmp_target_x 和 foot_zmp_target_y (足底ZMP目标位置)**
### 15. **walk_com_height (步态时的身体重心高度)**
### 16. **walk_foot_height (步态时的足部高度)**
### 17. **walk_trunk_pitch (步态时的躯干俯仰角度)**
18. **walk_foot_rise_ratio (步态时的脚升起比例)**



motion里的文件是随机抽取



算obs的地方：_reset_envs；post_physics_step

step是self.optimizer.step()调用？

通过common_play中的get_action得到action，env_step



训练效果一般

![image-20241113105133790](../../pictrue/image-20241113105133790.png)

![image-20241113105245801](../../pictrue/image-20241113105245801.png)

curriculum

The `__init__` function of `VecTask` triggers a call to `create_sim()`



仿真环境中执行action在pre_physics_step:

```python
def pre_physics_step(self, actions):

        if self.cfg["env"]["debugSaveObs"]:
            self.saved_actions.append(actions[0].cpu().numpy())
            pickle.dump(self.saved_actions, open("saved_actions.pkl", "wb"))

        self.prev_actions = self.actions.clone()
        self.actions = actions.to(self.device).clone()
        if self._pd_control == "isaac":

            tar = self.actions * self.power_scale + self._default_dof_pos
            tar_tensor = gymtorch.unwrap_tensor(tar)
            self.gym.set_dof_position_target_tensor(self.sim, tar_tensor)
        elif self._pd_control == "custom":
            self.render()
            for i in range(self.control_freq_inv):
                self.torques = self.p_gains * (
                    self.actions * self.power_scale
                    + self._default_dof_pos
                    - self._dof_pos
                ) - (self.d_gains * self._dof_vel)

                if self.randomize_torques:
                    self.torques *= self.randomize_torques_factors

                self.torques = torch.clip(
                    self.torques, -self.max_effort, self.max_effort
                )
                self.gym.set_dof_actuation_force_tensor(
                    self.sim, gymtorch.unwrap_tensor(self.torques)
                )
                self.gym.simulate(self.sim)
                if self.device == "cpu":
                    self.gym.fetch_results(self.sim, True)
                self.gym.refresh_dof_state_tensor(self.sim)
        else:
            print(f"Unknown PD control type {self._pd_control}. Exiting.")
            exit()
            # forces = self.actions * self.motor_efforts.unsqueeze(0) * self.power_scale
            # force_tensor = gymtorch.unwrap_tensor(forces)
            # self.gym.set_dof_actuation_force_tensor(self.sim, force_tensor)

        return
```



修改了base_task.c,加了轨迹可视化(未完成)



训练评价：

1. **`disc_loss`**：用于评估判别器的损失（discriminator loss），即在对抗学习中用于区分模拟数据与真实数据的模型的效果。相关的指标包括：
   - `disc_agent_acc`: 判别器在区分生成样本中的准确率。
   - `disc_demo_acc`: 判别器在区分真实样本中的准确率。
   - `disc_grad_penalty`: 判别器梯度的正则项，用于限制梯度的大小。
   - `disc_logit_loss`: 判别器logit的正则项。

2. **`actor_loss`** 和 **`critic_loss`**：
   - `actor_loss` 用于评估策略梯度方法中 actor 的损失，衡量策略对给定的行动产生的效果。
   - `critic_loss` 用于评估 critic 的损失，衡量 critic 对于状态值函数的估计准确性。
   - 相关的 `actor_clip_frac` 表示策略损失被截断的比例。

3. **`entropy`**：用于衡量策略的熵值（即随机性），更高的熵值代表模型的探索性更强，而更低的熵值则意味着模型的行为更确定性。

4. **`kl`** (Kullback-Leibler divergence)：用于衡量当前策略与旧策略之间的分布差异大小，监控策略是否过度偏离之前的策略。

5. **`play_time`** 和 **`update_time`**：用于衡量在一轮训练中，进行 roll-out 和参数更新的时间开销。这有助于分析训练效率。

6. **`disc_rewards`**：计算自适应运动先验（AMP）得到的奖励，用于鼓励生成类似于人类的运动，指标包括 `disc_reward_mean` 和 `disc_reward_std`。



1. **`actor_loss`** 和 **`critic_loss`**：损失越低表示 actor 和 critic 学习的越好。
2. **`disc_loss`**：越低意味着判别器在区分生成样本和真实样本上表现得更好。
3. **`disc_agent_acc`** 和 **`disc_demo_acc`**：反映了判别器的准确率，通常希望生成的样本和真实样本都接近 0.5 的准确率。
4. **`kl`**：衡量当前策略的变化，保持在一个合理的范围内非常重要，过大可能导致训练不稳定，过小则表明策略收敛速度较慢。
5. **`entropy`**：用来度量策略的随机性，过低意味着策略可能过度确定，缺乏探索，过高则可能意味着学习还不够稳定。
6. **`disc_reward_mean`** 和 **`disc_reward_std`**：用于评估 AMP 训练的效果，均值越高表示模型生成的行为越接近于专家行为，标准差可以反映生成行为的稳定性。



现状:critic loss一直增加



players/PPO_continuous get_action

```python
    def get_action(self, obs, is_deterministic = False):
        if self.has_batch_dimension == False:
            obs = unsqueeze_obs(obs)
        obs = self._preproc_obs(obs)
        input_dict = {
            'is_train': False,
            'prev_actions': None, 
            'obs' : obs,
            'rnn_states' : self.states
        }
        with torch.no_grad():
            res_dict = self.model(input_dict)
        mu = res_dict['mus']
        action = res_dict['actions']
        self.states = res_dict['rnn_states']
        if is_deterministic:
            current_action = mu
        else:
            current_action = action
        if self.has_batch_dimension == False:
            current_action = torch.squeeze(current_action.detach())

        if self.clip_actions:
            return rescale_actions(self.actions_low, self.actions_high, torch.clamp(current_action, -1.0, 1.0))
        else:
            return current_action
```

这里网络的输入obs就是obs_dict,后者赋值方式有：

```python
obs_dict = self.env_reset()
obs_dict, r, done, info = self.env_step(self.env, action)
```

通过RLGPUEnv得到的obs，要看这个env怎么定义的    self.env = env_configurations.configurations[config_name]["env_creator"](

​      **kwargs

​    )

确定环境：

vecenv.register(

  "RLGPU",

  lambda config_name, num_actors, **kwargs: RLGPUEnv(

​    config_name, num_actors, **kwargs

  ),

)

env_configurations.register(

  "rlgpu",

  {

​    "env_creator": lambda **kwargs: create_rlgpu_env(**kwargs),

​    "vecenv_type": "RLGPU",

  },

)

确实用了RLGPU，关键在于configname



### get_action

1. common_player:get_action->super().get_action

2. players:get_action（顺便把obs从字典中取出并进行了归一化标准化）

   ```python
   input_dict = {
               'is_train': False,
               'prev_actions': None, 
               'obs' : obs,
               'rnn_states' : self.states
           }
   with torch.no_grad():
       res_dict = self.model(input_dict)
   ```

   

   

#### step

1. common_player:`obs_dict, r, done, info = self.env_step(self.env, action)`->`obs, rewards, dones, infos = env.step(actions)`
2. vec_task:class VecTaskPython:step
3. base_task:step



### rewards(主要迭代在amp_agent里，显示在common_agent.py里，后者会调用前者的train_epoch)

1. duckling的poststep中调用具体任务里的`_compute_reward`函数得到rew_buf(不包含disc_reward)
1. vec_task中rew_buf作为step的参数被调用
1. 写到amp_agent的experience_buffer里需要的时候再读出来



（输出的）rewards是不包括风格奖励的，风格奖励后来只用来训练并记在batch中

update_data就是在更新tensor_dict

![image-20250219223939173](../../pictrue/image-20250219223939173.png)

#### 姿态

1. base_task的step
2. duckling的pre_physics_step







主要问题：

1. 加入域随机化
2. sim2sim
3. actor和critic以及disciminator的lr是一个吗





### 第七周

生成了可用模型

1. 改为只走正向？
2. 一阶段训练好步态后大幅调整权重？
3. 训练站立等步态及过渡步态

地形鲁棒性，横行运动，抗推动，头部运动







reward在rl-games中是env_step得到的，在awd中是step通过compute_reward得到的，这两个怎么关联(这俩是一个)

Duckling_reward呢







转换步态:

Disney方案



站立模态:

rew_survive+rew_stand(contact)(+rew_style)(+rew_default(no_command/no push))







导出和配置不带头的模型并改了一部分urdf模型；想用survive_reward+init_reward(与初始姿态偏离的L2范数)+stand_reward(双脚接触)+smooth_reward做一个站立模态和过渡模态，没跑通还在debug；调整task_reward和style_reward权重训练了两版模型但是提升效果不明显



survive_reward+init_reward(与初始姿态偏离的L2范数)+stand_reward(双脚接触)+smooth_reward(也试下保留和去掉的区别rew_lin_vel_xy + rew_ang_vel_z+rew_torque)



`acquire_net_contact_force_tensor(self.sim)`返回一个形状为 `(num_rigid_bodies, 3)` 的张量，表示每个刚体在 `X`、`Y` 和 `Z` 方向上的接触力。



接触集合模式(contact collection mode)决定是否收集和怎么样收集接触数据

在init中用acquire得到后似乎会直接绑定，后面直接refresh即可



### 2_16

找到是哪个reward出了问题(或者是代码结构(或那个AMP学习的reward权重)有问题)







快速配环境：

```python
cuda-python
Flask==3.0.3
meshcat==0.3.2
numpy==1.23.0
numpy-stl==3.1.2
placo==0.6.2
pybullet==3.2.1
PyYAML==6.0.2
rl-games==1.1.4
scipy==1.10.1
six==1.16.0
tensorboard==2.14.0
tensorboard-data-server==0.7.2
tensorboardX==2.6.2.2
termcolor==2.4.0
cmeel-boost==1.83.0
gym==0.26.2
pygame
```



### 仿真效果

1. 3_9:

   1. 6_0:站起来了但是很奇怪，偏离初始状态较多

      ![image-20250309174616552](../../pictrue/image-20250309174616552.png)

      6：还在踏步而且有轻微位移

      5_0：![image-20250309174554526](../../pictrue/image-20250309174554526.png)

      5:和6基本一样 

      4_0:![image-20250309174650346](../../pictrue/image-20250309174650346.png)

      4:和5，6一样

      结论：要站立确实需要disc_reward设为0

   2.  3_10:

      _5_10900:怪的离谱，头都要掉了![image-20250310114954650](../../pictrue/image-20250310114954650.png)

      5_standstill5:更怪了，还会动，而且螃蟹走路，头也要掉了![image-20250310115637496](../../pictrue/image-20250310115637496.png)

      5_standstill0.5:同上

      5_standstill0.05:同上，但是不动了

      5_standstill0.2:同上，在动但是不位移

      5_standstill0.2:同上，无敌圆规，要把我的头都笑掉了

      5_standstill5_scratch:不动但是姿势好奇怪，在后仰![image-20250310120922913](../../pictrue/image-20250310120922913.png)

      5_standstill0.5_scratch：甚至有的站不稳，而且举头望月2.0![image-20250310121136852](../../pictrue/image-20250310121136852.png)

      5_standstill0.05_scratch：同上

   3. 3_11(改变了default_pos):

      standstill0.05：![image-20250311111942348](../../pictrue/image-20250311111942348.png)

      standstill0.5：![image-20250311112055481](../../pictrue/image-20250311112055481.png)

      standstill5：

      ![image-20250311112320249](../../pictrue/image-20250311112320249.png)

      standstill2：![image-20250311112451055](../../pictrue/image-20250311112451055.png)

      standstill0.2：![image-20250311113140701](../../pictrue/image-20250311113140701.png)

      standstill0.2_10900：还在动

      standstill2_10900：没动了但是很奇怪

      standstill5_10900：同上

      standstill0.5_10900：还在动，姿势和前面的一样

      

   4. 3_25下的都不错，如standstill0.*
   
   4. 加了效果正常



### 问题

1. 三个变量，是否用h和怎么用rew_lin_vel_xy；disc_reward_w:是否取0；生成的motion和全0motion
2. 3_31:似乎没做舵机系统辨识




### 训练日志

1. 3_9:看看在10900上训练效果会不会好；看看stand_still_reward效果怎么样

   注意：除了_5_10900外，没加sratch后缀的都是从10900基础上训练的

2.  3_10:想加上柔顺奖励(速度/加速度)，要在duckling.py819行加上前两次的action然后补一个加速度奖励；只观测一个机器人并输出角度;把default_pos改为了Init_pos

   注意：这次除了加了10900的外都是从头训练的

3. 3_11:把结果的第一个环境的关节角度打印出来看看到底什么情况

4. 3_25:确定了default_pos就是复位之后的pos；我脑子有坑吗，站住明显要让standstill参数为负数啊，今天试试全部改为负的效果，配置文件还是叫原来的；350后缀的是用学姐的勉强站立模型开始站立的；放在350下的文件夹里

5. 3_26:加域随机化（后缀2）和push（后缀3）

6. 3_27:要部署了想起之前的跟踪速度角速度一般，把command_3中的相关参数变为了原来的四倍，resume接着训试一试

7. 3_31:up是用一个策略实现的，可以试试把站立(指令较小)设置为一个概率，否则不会数值较小；在站立时关掉amp的参数；但好像不用这么麻烦；-

8. 4_1：left:[0-5] right:[10-15]

   双脚跳：奖励向前(x)，惩罚旋转和横移；奖励腾空时间和高度(正常站立actual_base_height约0.15)，起跳高度等于目标高度；奖励存活；奖励直立；惩罚速度，加速度；奖励对称，对称接触力；惩罚力矩（写奖励的时候已经考虑正负，在配置中正都取正即可）

9. 4_2:双脚跳无法离地；看奖励发现是速度和角速度跟随在主导训练；后面把跳跃奖励大幅度提高，限制奖励大幅调小，看看效果;加了个extreme版本只包含跳跃和镜像奖励

   看了站立奖励之后发现stand_still好像压根没起作用，模型自己会停

9.  4_4:加上bam看看；限制策略幅度；卡尔曼滤波；硬train一发训出来的不动



### debug日志

1. torc——h.sum结果只有一个维度，不能dim=1(但是duckling_command就是这么写的)

   ```
   rew_stand_still = (
       torch.sum(torch.norm(dof_pos - default_dof_pos), dim=1)
       * (torch.norm(commands, dim=1) < 0.01)
       * rew_scales["stand_still"]
   )
   ```

   好像是L2正则化有问题，norm会改变维度吗

2. run和run_train分别实例化了AMPPlayerContinuous和哪个类呢

3. reward中的各个参数shape都是带环境数目的,最后算出来的reward也是每个环境单独奖励的；算奖励时只需要单独算一个环境的

2. 

### run中模型加载过程

1. 在torch_runner中实例化AMPPlayerContinuous并把模型加载到该类中

2. ```
   restore模型(各级restore不同部分)：
          if (fn != 'Base'):
               super().restore(fn)
               if self._normalize_amp_input:
                   checkpoint = torch_ext.load_checkpoint(fn)
                   self._amp_input_mean_std.load_state_dict(checkpoint['amp_input_mean_std'])
   ```

3. 





{"kt": 1.21164135295077, "R": 2.6761663274455603, "armature":  0.02840336348682085, "q_offset": -0.05116067663549731, "friction_base":  0.05239296084748866, "friction_viscous": 0.05908515565091076, "model":  "m1", "actuator": "sts3215"}



<joint damping="0.56" frictionloss="0.068" armature="0.027"/>

   <!-- <position kp="17.12" kv="0.0" forcerange="-3.23 3.23"/> -->

   <position kp="13.37" kv="0.0" forcerange="-3.23 3.23"/>



```
    def to_mujoco(self):
        if self.vin == 0 or self.kp == 0:
            print(yellow(f"WARNING: kp or vin are not set"))

        kt = self.model.kt.value
        R = self.model.R.value

        kp = self.error_gain * self.kp * self.vin * self.max_pwm * kt / R
        damping = self.model.friction_viscous.value + kt**2 / R

        print_parameter("forcerange", self.vin * self.model.kt.value / R)
        print_parameter("armature", self.model.armature.value)
        print_parameter("kp", kp)
        print_parameter("damping", damping)
        print_parameter("frictionloss", self.model.friction_base.value)
```





==4_11:mujoco和isaacgym关节驱动的区别==

mujoco中dof是分为joint和acuator两部分的:

joint参数有damping,stiffness，这里这俩真的是阻尼(给torque施加damping\*v的反力矩)和弹性(施加stiffness\*(-p)的力矩)的意思；frictionloss摩擦损失(这里看到bam直接把库伦摩擦系数赋值给了frictionloss);armature电枢

acuator参数有:kp,kv



isaac gym中dof就是dof，有以下参数:

friction:库伦摩擦系数

damping:这里用作kv（但是也有说也作为阻尼，还需要验证）

stiffness：这里用作kp



部署不出来：对一下imu和关节输出是否对应等



行走：

```
pygame 2.6.0 (SDL 2.28.4, Python 3.11.2)
Hello from the pygame community. https://www.pygame.org/contribute.html
{10: -0.06713327063585416, 11: 89.56894574312794, 12: -33.97509584541677, 13: -11.29125199022908, 14: -53.54233900070485, 20: -1.555385732444946, 21: 89.02257041795924, 22: 24.03200021261404, 23: 192.3133754130558, 24: -38.989512792341486, 30: -75.94366926962348, 31: 38.64788975654116, 32: 179.9087476710785}
Starting
[0 0 0]
Observation: [ 0.         -0.         -1.          0.051      -1.541      -0.421
 -3.123       0.664       1.323      -0.688      -3.142       0.
  0.          0.01       -1.564       0.582       0.162       0.94
 -0.         -0.         -0.         -0.02398082 -0.02398082 -0.
 -0.02398082 -0.02398082  0.          0.         -0.02398082 -0.02398082
 -0.02398082 -0.02398082 -0.02398082  0.          0.          0.
  0.          0.          0.          0.          0.          0.
  0.          0.          0.          0.          0.          0.
  0.          0.          0.        ]
obs shape: (51,)
Action: {'right_hip_yaw': 0.05120728505350735, 'right_hip_roll': -2.0069231670172787, 'right_hip_pitch': 0.7617848374479319, 'right_knee': 0.3696733993004959, 'right_ankle': 0.8168156795369388, 'left_hip_yaw': -0.025832874580189104, 'left_hip_roll': -1.7574264630713998, 'left_hip_pitch': -0.4233936537366081, 'left_knee': -3.263059231054581, 'left_ankle': 1.4000674392355492, 'neck_pitch': 1.2221601852665704, 'head_pitch': -0.5924240625013548, 'head_yaw': -3.4227427089214326}
{10: -2.9339613138893132, 11: 114.9882272771189, 12: -43.64705608282596, 13: -21.180725578172854, 14: -46.80009107757695, 20: 1.480114686135624, 21: 100.69311913859504, 22: 24.258669431731022, 23: 186.95952224063123, 24: -80.21795530188581, 30: -70.02462050470126, 31: 33.943398463322126, 32: 196.1087115803725}
[0 0 0]
Observation: [-6.97130701e-02  8.96340037e-02 -9.93531999e-01  5.10000000e-02
 -1.54100000e+00 -4.21000000e-01 -3.12300000e+00  6.64000000e-01
  1.32300000e+00 -6.88000000e-01 -3.14200000e+00  0.00000000e+00
  0.00000000e+00  1.00000000e-02 -1.56400000e+00  5.82000000e-01
  1.62000000e-01  9.40000000e-01 -4.31654831e-01 -2.47002486e+00
 -5.75539774e-01 -7.19424718e-02  5.03597302e+00 -1.07913708e+00
  4.31654831e-01  7.19424718e-02  0.00000000e+00  0.00000000e+00
  4.31654831e-01 -4.19664419e+00  1.58273438e+00  8.63309661e-01
 -1.65467685e+00 -5.29794767e-02 -2.03689501e-01 -3.95612419e-03
  9.34423655e-02  7.19572067e-01 -1.03306890e-01  8.21088627e-02
 -2.82742709e-01 -1.52745266e-02  4.98122303e-03  5.00355884e-02
 -4.43650156e-01  1.68807551e-01  1.72603875e-01 -1.17674425e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': 0.08474566382862712, 'right_hip_roll': -2.0071775298388577, 'right_hip_pitch': 0.5855084814661051, 'right_knee': 0.29519394603482896, 'right_ankle': 0.795973648892522, 'left_hip_yaw': 0.020160889373258238, 'left_hip_roll': -1.8538009002843439, 'left_hip_pitch': -0.4569717068534065, 'left_knee': -3.0544653409836657, 'left_ankle': 1.3213928844107201, 'neck_pitch': 1.258980216969089, 'head_pitch': -0.6225853575875002, 'head_yaw': -3.4688076221942903}
{10: -4.855568869414816, 11: 115.00280119326041, 12: -33.54716485712161, 13: -16.91336724560828, 14: -45.60593068516954, 20: -1.1551338723178484, 21: 106.21496764384527, 22: 26.182550159589667, 23: 175.00797270735194, 24: -75.7102353553525, 30: -72.13425292279346, 31: 35.67151337640693, 32: 198.74803669454343}
[0 0 0]
Observation: [ 0.11329634  0.21657128 -0.96967047  0.005      -1.751      -0.437
 -3.145       1.349       1.259      -0.644      -3.14        0.
  0.          0.039      -1.955       0.707       0.289       0.812
  0.19184659 -1.53477273 -0.35971236  1.58273438 -0.74340554  0.28776989
 -0.         -0.35971236  0.          0.          0.31175071 -0.5035973
 -1.96642756  0.19184659 -0.11990412 -0.00698571 -0.30006394 -0.03753418
  0.30203626  0.64089751 -0.06648686  0.05194757 -0.32880762 -0.01380514
  0.00390185  0.08357397 -0.44390452 -0.0074688   0.09812442 -0.13851646
  0.          0.          0.        ]
obs shape: (51,)
Action: {'right_hip_yaw': -0.008533612214549522, 'right_hip_roll': -2.0004439633162594, 'right_hip_pitch': 1.1152492173545863, 'right_knee': 0.21528807100764924, 'right_ankle': 0.7946075551377536, 'left_hip_yaw': 0.06135793973608363, 'left_hip_roll': -1.6367680653968393, 'left_hip_pitch': -0.3535696883063484, 'left_knee': -2.7440425926564105, 'left_ankle': 1.3937232400549462, 'neck_pitch': 1.15917464583023, 'head_pitch': -0.5774828246344763, 'head_yaw': -3.411377593278885}
{10: 0.48893996389497557, 11: 114.61699625044494, 12: -63.899073259686, 13: -12.335097848251081, 14: -45.52765927860214, 20: -3.5155509864956405, 21: 93.77990218903162, 22: 20.25805090370978, 23: 157.22205936334848, 24: -79.8544594644469, 30: -66.41581492464415, 31: 33.08732859284894, 32: 195.4575384203764}
[0 0 0]
Observation: [ 0.11329634  0.21657128 -0.96967047  0.019      -1.834      -0.456
 -3.043       1.328       1.201      -0.611      -3.146       0.
  0.          0.081      -1.991       0.579       0.306       0.803
  0.28776989  2.90167969  0.86330966  3.88489348  0.74340554 -0.52757813
 -0.11990412  0.11990412  0.          0.         -0.57553977  0.0959233
  4.98801138 -1.55875355 -0.07194247  0.03421134 -0.0830311   0.06586784
  0.612459    0.71322787 -0.16629243  0.0970501  -0.27137759 -0.01331597
 -0.00597674 -0.00970531 -0.43717095  0.52227193  0.01821855 -0.13988255
  0.          0.          0.        ]
obs shape: (51,)
Action: {'right_hip_yaw': -0.0032793864091477188, 'right_hip_roll': -1.9261982422144983, 'right_hip_pitch': 1.086457432114413, 'right_knee': 0.15942923170439416, 'right_ankle': 0.8936882369385959, 'left_hip_yaw': 0.03875033290042031, 'left_hip_roll': -1.65644410998016, 'left_hip_pitch': -0.26378485749770886, 'left_knee': -3.0145358020184405, 'left_ankle': 1.2488721515310814, 'neck_pitch': 1.181648800660209, 'head_pitch': -0.5891932821382719, 'head_yaw': -3.4068348848819734}
{10: 0.18789500063672646, 11: 110.36302978440864, 12: -62.249425480777006, 13: -9.134622107675082, 14: -51.20456417706907, 20: -2.220230529921022, 21: 94.90725650116713, 22: 15.113759034078567, 23: 172.72017864674135, 24: -71.55510343415358, 30: -67.7034891445255, 31: 33.75828838398373, 32: 195.19726040167475}
[0 0 0]
Observation: [ 1.04640101e-01  1.58859286e-01 -9.81740381e-01  5.40000000e-02
 -1.62700000e+00 -3.66000000e-01 -2.77000000e+00  1.38800000e+00
  1.14500000e+00 -6.10000000e-01 -3.14600000e+00  0.00000000e+00
  0.00000000e+00 -2.00000000e-03 -1.98600000e+00  1.09200000e+00
  2.31000000e-01  8.06000000e-01  1.67865767e-01 -1.19904120e-01
  2.06235086e+00 -2.56594816e+00 -2.47002486e+00 -1.43884944e-01
  1.43884944e-01  2.39808239e-02  0.00000000e+00  0.00000000e+00
 -9.59232957e-02  7.43405542e-01 -3.83693183e-01 -1.00719460e+00
  1.51079191e+00  1.16037307e-02 -1.02707148e-01  1.55652672e-01
  3.41965795e-01  5.68376780e-01 -1.43818274e-01  8.53396431e-02
 -2.66834885e-01 -1.27670476e-02 -3.78026103e-04 -4.45108302e-03
 -3.62925231e-01  4.93480146e-01 -3.76402922e-02 -4.08018678e-02
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': 0.07385890526272441, 'right_hip_roll': -1.8883072715075586, 'right_hip_pitch': 0.9906477936141993, 'right_knee': 0.04858971950523072, 'right_ankle': 0.6168119214640857, 'left_hip_yaw': 0.1397831236283337, 'left_hip_roll': -1.7079964205661355, 'left_hip_pitch': -0.5281864125590492, 'left_knee': -2.8102375441906817, 'left_ankle': 1.4874085094107201, 'neck_pitch': 1.2254015901575845, 'head_pitch': -0.6120459339131552, 'head_yaw': -3.3616102331876756}
{10: -4.231803551010693, 11: 108.19203708124715, 12: -56.75993755804065, 13: -2.783985855374215, 14: -35.3407198532469, 20: -8.008983031058936, 21: 97.86098632189113, 22: 30.262852235789218, 23: 161.01475071133524, 24: -85.22223000107905, 30: -70.21033932464944, 31: 35.067648881366694, 32: 192.60607872964232}
[0 0 0]
Observation: [ 0.19084164  0.26201472 -0.94600621  0.056      -1.655      -0.229
 -2.872       1.25        1.109      -0.579      -3.14        0.
  0.         -0.01       -1.937       1.064       0.162       0.895
  0.91127131 -1.1031179  -2.90167969  2.01438921  3.35731535  0.02398082
 -0.07194247 -0.43165483  0.          0.          0.91127131  0.33573153
 -0.95923296 -1.53477273 -4.0047976   0.11263652 -0.15425946 -0.10874888
  0.54626405  0.80691314 -0.10006548  0.06248699 -0.22161023 -0.01536139
 -0.01148235  0.07268721 -0.32503426  0.39767051 -0.1484798  -0.31767818
  0.          0.          0.        ]
obs shape: (51,)
Action: {'right_hip_yaw': 0.05968271536327984, 'right_hip_roll': -1.837495682743368, 'right_hip_pitch': 0.937415123783877, 'right_knee': 0.19200737732387596, 'right_ankle': 0.5503983400927783, 'left_hip_yaw': 0.08766759757800449, 'left_hip_roll': -1.6881706193128168, 'left_hip_pitch': -0.6803863067488838, 'left_knee': -2.5358622843144305, 'left_ankle': 1.407752862132888, 'neck_pitch': 1.2202303358803552, 'head_pitch': -0.60820327461855, 'head_yaw': -3.36399739921093}
{10: -3.4195677001965326, 11: 105.28074749470467, 12: -53.70993024454979, 13: -11.001212356034, 14: -31.535501938322327, 20: -5.022983341270975, 21: 96.72505158461078, 22: 38.98326381520444, 23: 145.29420631762088, 24: -80.65829759767654, 30: -69.91404827977522, 31: 34.8474807216791, 32: 192.7428532677718}
[0 0 0]
Observation: [ 0.18616881  0.37751647 -0.90709563  0.107      -1.728      -0.446
 -2.744       1.466       1.107      -0.596      -3.134       0.
  0.          0.062      -1.92        0.984       0.059       0.625
 -0.23980824  0.04796165 -3.06954546  3.93285512 -1.1031179   0.23980824
 -0.16786577 -0.19184659  0.          0.          0.11990412  0.79136719
 -1.1990412   2.27817827 -1.12709872  0.060521   -0.13443366 -0.26094878
  0.82063931  0.72725749 -0.10523674  0.06632965 -0.2239974  -0.01134934
 -0.0097386   0.05851102 -0.27422267  0.34443784 -0.00506215 -0.38409176
  0.          0.          0.        ]
obs shape: (51,)
Action: {'right_hip_yaw': 0.04407806289889004, 'right_hip_roll': -2.0214305501254177, 'right_hip_pitch': 1.0762992509239222, 'right_knee': 0.1387672741424244, 'right_ankle': 0.5058985255824329, 'left_hip_yaw': 0.1252160464684521, 'left_hip_roll': -1.5090991631188928, 'left_hip_pitch': -0.562843756781118, 'left_knee': -2.6739299470303424, 'left_ankle': 1.330949416316848, 'neck_pitch': 1.1858130791674417, 'head_pitch': -0.591613595794602, 'head_yaw': -3.3950078332424165}
{10: -2.525486973218578, 11: 115.81943910099464, 12: -61.66740457103271, 13: -7.950779142895798, 14: -28.98585037776451, 20: -7.174350989956302, 21: 86.46501291343714, 22: 32.24857178884587, 23: 153.2049006784784, 24: -76.25778430035574, 30: -67.94208472770697, 31: 33.89696214158933, 32: 194.51962025864486}
[0 0 0]
Observation: [ 0.36731068  0.56696811 -0.7373127   0.097      -1.721      -0.624
 -2.539       1.399       1.148      -0.607      -3.151       0.
  0.          0.067      -1.87        0.921       0.202       0.559
  0.45563565  0.5995206   0.91127131 -0.76738637 -1.31894532 -0.11990412
  0.26378906  0.14388494  0.          0.         -0.0959233  -2.15827415
  1.79856179 -0.93525213 -0.83932884  0.09806944  0.0446378  -0.14340623
  0.68257165  0.65045404 -0.139654    0.08291933 -0.25500783 -0.0142063
 -0.01036228  0.04290637 -0.45815754  0.48332196 -0.05830225 -0.42859158
  0.          0.          0.        ]
obs shape: (51,)
Action: {'right_hip_yaw': 0.040062661893145106, 'right_hip_roll': -1.9022640269072626, 'right_hip_pitch': 1.0785928078525568, 'right_knee': 0.15734558370820695, 'right_ankle': 0.7117663823233844, 'left_hip_yaw': 0.1319284980456387, 'left_hip_roll': -1.5616986975112497, 'left_hip_pitch': -0.45387378524352795, 'left_knee': -2.8186901980755694, 'left_ankle': 1.3528242017401269, 'neck_pitch': 1.1975309798012537, 'head_pitch': -0.5916379815448958, 'head_yaw': -3.3972689652442933}
{10: -2.2954214425368074, 11: 108.99170026134662, 12: -61.79881570311647, 13: -9.015237871502663, 14: -40.78120970642489, 20: -7.5589461355150265, 21: 89.4787442384724, 22: 26.005052326081255, 23: 161.49905210462416, 24: -77.51111718286391, 30: -68.61347097877807, 31: 33.89835934216142, 32: 194.64917357927436}
[0 0 0]
Observation: [ 0.53001929  0.82263096 -0.20581023  0.117      -1.695      -0.579
 -2.577       1.322       1.145      -0.593      -3.152       0.
  0.          0.053      -1.979       1.05        0.15        0.513
  0.21582742 -0.04796165  1.07913708 -1.87050427  0.16786577 -0.
 -0.19184659 -0.          0.          0.         -0.          1.05515625
 -0.02398082  0.16786577  3.18944958  0.1047819  -0.00796174 -0.03443626
  0.5378114   0.67232883 -0.12793609  0.08289494 -0.25726897 -0.01697956
 -0.00874778  0.03889097 -0.33899102  0.48561552 -0.03972394 -0.22272372
  0.          0.          0.        ]

```



站立：

```
Hello from the pygame community. https://www.pygame.org/contribute.html
{10: -0.06713327063585416, 11: 89.56894574312794, 12: -33.97509584541677, 13: -11.29125199022908, 14: -53.54233900070485, 20: -1.555385732444946, 21: 89.02257041795924, 22: 24.03200021261404, 23: 192.3133754130558, 24: -38.989512792341486, 30: -75.94366926962348, 31: 38.64788975654116, 32: 179.9087476710785}
Starting
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01  4.10000000e-02
 -1.54900000e+00 -4.20000000e-01 -3.08600000e+00  6.90000000e-01
  1.28800000e+00 -6.65000000e-01 -3.14200000e+00  0.00000000e+00
  0.00000000e+00 -5.00000000e-03 -1.56900000e+00  5.73000000e-01
  1.34000000e-01  9.20000000e-01 -0.00000000e+00 -2.39808239e-02
 -2.39808239e-02 -0.00000000e+00 -0.00000000e+00 -2.39808239e-02
 -0.00000000e+00 -4.79616478e-02  0.00000000e+00  0.00000000e+00
 -2.39808239e-02 -2.39808239e-02 -0.00000000e+00 -0.00000000e+00
 -0.00000000e+00  0.00000000e+00  0.00000000e+00  0.00000000e+00
  0.00000000e+00  0.00000000e+00  0.00000000e+00  0.00000000e+00
  0.00000000e+00  0.00000000e+00  0.00000000e+00  0.00000000e+00
  0.00000000e+00  0.00000000e+00  0.00000000e+00  0.00000000e+00
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': -0.09348847376607274, 'right_hip_roll': -1.6589377429159258, 'right_hip_pitch': 0.3759934910171534, 'right_knee': 0.031124545307080087, 'right_ankle': 0.7307619504796268, 'left_hip_yaw': -0.06268410186366688, 'left_hip_roll': -1.6532711535730897, 'left_hip_pitch': -0.1790505219559837, 'left_knee': -3.4343225234864123, 'left_ankle': 0.6979137341750673, 'neck_pitch': 1.1434815773258966, 'head_pitch': -0.9827169230689246, 'head_yaw': -3.01578484416008}
{10: 5.356494979915484, 11: 95.05013114404133, 12: -21.54284015967292, 13: -1.783305085359402, 14: -41.86957559123068, 20: 3.5915344793562505, 21: 94.72545949046301, 22: 10.258839227692347, 23: 196.77218608248998, 24: -39.9875114324466, 30: -65.51666833173617, 31: 56.305532147931785, 32: 172.79174348989127}
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01  4.10000000e-02
 -1.55100000e+00 -4.20000000e-01 -3.07700000e+00  6.91000000e-01
  1.28800000e+00 -6.65000000e-01 -3.14300000e+00  0.00000000e+00
  0.00000000e+00 -5.00000000e-03 -1.57000000e+00  5.75000000e-01
  1.34000000e-01  9.21000000e-01 -6.71463070e-01 -1.65467685e+00
  3.14148793e+00 -1.43884944e-01 -2.39808239e-01 -6.23501422e-01
 -2.03837003e+00  8.87290485e-01  0.00000000e+00  0.00000000e+00
 -1.48681108e+00 -1.22302202e+00 -2.49400569e+00 -1.39088779e+00
 -2.82973722e+00 -8.98307040e-02 -9.95341912e-02  2.40387008e-01
 -7.78209269e-02  1.74183622e-02 -1.81985497e-01 -3.08183998e-01
  1.24215156e-01 -1.90521032e-01 -9.72314328e-02 -9.46601704e-02
 -9.56647322e-02 -2.16983795e-01 -1.65944979e-01 -2.03728154e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': -0.04080904679797504, 'right_hip_roll': -1.5987499635489557, 'right_hip_pitch': 0.33134126743011727, 'right_knee': -0.10049277725704497, 'right_ankle': 0.7733483217822315, 'left_hip_yaw': -0.09079368214206349, 'left_hip_roll': -1.6441498771348535, 'left_hip_pitch': -0.22072063575793988, 'left_knee': -3.752024846684731, 'left_ankle': 0.7307887430561594, 'neck_pitch': 1.1106305071602625, 'head_pitch': -1.1223826459159094, 'head_yaw': -3.0563246974349023}
{10: 2.3381861474758363, 11: 91.60162540804937, 12: -18.984456202261246, 13: 5.757812008376942, 14: -44.30959493164697, 20: 5.20209479319255, 21: 94.20284884677996, 22: 12.646360880374278, 23: 214.97518834325484, 24: -41.87111069278828, 30: -63.63444065875719, 31: 64.3077886097079, 32: 175.1145059846182}
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01 -4.00000000e-03
 -1.67200000e+00 -1.93000000e-01 -3.07900000e+00  6.67000000e-01
  1.08400000e+00 -7.50000000e-01 -3.02300000e+00  0.00000000e+00
  0.00000000e+00 -1.01000000e-01 -1.67500000e+00  3.57000000e-01
 -1.20000000e-02  7.28000000e-01 -8.63309661e-01  2.39808239e-02
 -1.67865767e-01 -2.39808239e-02  6.95443894e-01 -1.46283026e+00
 -2.39808239e-02 -2.63789063e-01  0.00000000e+00  0.00000000e+00
  9.59232957e-02  5.27578126e-01 -1.43884944e-01 -1.72661932e+00
  5.03597302e-01 -1.17940284e-01 -9.04129148e-02  1.98716894e-01
 -3.95523250e-01  5.02933711e-02 -2.14836568e-01 -4.47849721e-01
  8.36753026e-02 -1.13959238e-01 -6.63189963e-02 -4.19807434e-02
 -3.54769528e-02 -2.61636019e-01 -2.97562301e-01 -1.61141783e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': -0.08228516238234852, 'right_hip_roll': -1.688353059795675, 'right_hip_pitch': 0.3813265421026255, 'right_knee': 0.013530461163441476, 'right_ankle': 0.7157802485095264, 'left_hip_yaw': -0.061849182351395006, 'left_hip_roll': -1.6750625222960054, 'left_hip_pitch': -0.1960783321719337, 'left_knee': -3.5298215919850238, 'left_ankle': 0.6996488179338983, 'neck_pitch': 1.0377954491864008, 'head_pitch': -1.0240160575617987, 'head_yaw': -2.9449921095371248}
{10: 4.714592521057217, 11: 96.73550465429089, 12: -21.848401478798134, 13: -0.7752383195308662, 14: -41.01118729842109, 20: 3.5436971150699508, 21: 95.97401294809947, 22: 11.23446088741603, 23: 202.24387965489115, 24: -40.08692440892931, 30: -59.461299236264246, 31: 58.671798251916634, 32: 168.73561857580628}
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01 -5.30000000e-02
 -1.65900000e+00 -2.02000000e-01 -3.08000000e+00  7.13000000e-01
  9.57000000e-01 -7.48000000e-01 -3.05000000e+00  0.00000000e+00
  0.00000000e+00 -9.10000000e-02 -1.62400000e+00  3.45000000e-01
 -1.14000000e-01  7.59000000e-01  4.79616478e-02 -9.59232957e-02
 -2.39808239e-02 -2.39808239e-02 -2.63789063e-01 -1.43884944e-01
 -2.39808239e-02  6.71463070e-01  0.00000000e+00  0.00000000e+00
 -4.79616478e-02 -1.12709872e+00  4.07674007e-01  7.67386366e-01
 -8.15348013e-01 -8.89957845e-02 -1.21325560e-01  2.23359197e-01
 -1.73319995e-01  1.91534460e-02 -2.87671626e-01 -3.49483132e-01
  1.95007890e-01 -1.77746594e-01 -1.62685618e-01 -8.34568590e-02
 -1.25080049e-01 -2.11650744e-01 -1.83539063e-01 -2.18709856e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': -0.10055905240081166, 'right_hip_roll': -1.6639766599805925, 'right_hip_pitch': 0.3854810603492762, 'right_knee': -0.024701328902323905, 'right_ankle': 0.7265991322861911, 'left_hip_yaw': -0.05397277872161519, 'left_hip_roll': -1.6740476936140596, 'left_hip_pitch': -0.20620757530738598, 'left_knee': -3.5046219849703677, 'left_ankle': 0.7116831149233392, 'neck_pitch': 1.0288796672116083, 'head_pitch': -1.0041634789218146, 'head_yaw': -2.999188348054886}
{10: 5.761609294401397, 11: 95.33883982516318, 12: -22.08643784024131, 13: 1.4152818944676782, 14: -41.63106367786654, 20: 3.092412429342045, 21: 95.91586754769514, 22: 11.814823768739306, 23: 200.8000485275631, 24: -40.77643883583127, 30: -58.95046255804982, 31: 57.53432928339397, 32: 171.84083430835835}
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01 

-4.70000000e-02 -1.66200000e+00 -2.09000000e-01 -3.08200000e+00  6.88000000e-01
  9.49000000e-01 -7.50000000e-01 -2.95000000e+00  0.00000000e+00  0.00000000e+00 
  -9.30000000e-02 -1.69500000e+00  3.80000000e-01 -7.00000000e-02  7.14000000e-01 
  
  4.79616478e-02 -7.19424718e-02 -2.39808239e-02 -2.39808239e-02  2.39808239e-02 
  -4.79616478e-02 -2.39808239e-02 -3.35731535e-01  0.00000000e+00  0.00000000e+00
 -7.19424718e-02  4.79616478e-02 -2.39808239e-02 -0.00000000e+00 2.39808239e-02 
 
 -8.11193809e-02 -1.20310731e-01  2.13229954e-01 -1.48120388e-01  3.11877429e-02 
 -2.96587408e-01 -3.29630554e-01  1.40811652e-01 -1.68001622e-01 -1.63598672e-01 
 -1.01730749e-01 -1.00703649e-01 -2.07496226e-01 -2.21770853e-01 -2.07890972e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': -0.08661490338347767, 'right_hip_roll': -1.6915225367816065, 'right_hip_pitch': 0.40104591926269784, 'right_knee': -0.012938724784930411, 'right_ankle': 0.7229448609219791, 'left_hip_yaw': -0.05236891458825719, 'left_hip_roll': -1.6730507463255464, 'left_hip_pitch': -0.2048497665982414, 'left_knee': -3.4954024130223162, 'left_ankle': 0.722338264740806, 'neck_pitch': 1.0259742984066766, 'head_pitch': -1.0154752186049658, 'head_yaw': -2.966367571949959}
{10: 4.962668406806665, 11: 96.91710230884861, 12: -22.97823856469695, 13: 0.7413343224578264, 14: -41.421689351501676, 20: 3.0005177835882244, 21: 95.85874667566634, 22: 11.737027060319214, 23: 200.27180596602255, 24: -41.386933950451706, 30: -58.783997187598274, 31: 58.18244422618919, 32: 169.96034235720222}
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01 -4.20000000e-02
 -1.66900000e+00 -2.11000000e-01 -3.08000000e+00  6.96000000e-01
  9.48000000e-01 -7.50000000e-01 -3.00400000e+00  0.00000000e+00
  0.00000000e+00 -1.03000000e-01 -1.69200000e+00  3.78000000e-01
 -7.00000000e-02  7.17000000e-01 -0.00000000e+00 -2.39808239e-02
 -2.39808239e-02 -2.39808239e-02  1.43884944e-01 -2.39808239e-02
 -2.39808239e-02  1.67865767e-01  0.00000000e+00  0.00000000e+00
 -0.00000000e+00 -1.19904120e-01 -4.79616478e-02 -4.79616478e-02
 -0.00000000e+00 -7.95155168e-02 -1.19313784e-01  2.14587763e-01
 -1.38900816e-01  4.18428928e-02 -2.99492776e-01 -3.40942293e-01
  1.73632428e-01 -1.66889995e-01 -1.75853431e-01 -8.77866000e-02
 -1.28249526e-01 -1.91931367e-01 -2.10008249e-01 -2.11545244e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': -0.0911498631765685, 'right_hip_roll': -1.680828748253164, 'right_hip_pitch': 0.4077148147457148, 'right_knee': -0.01229638042934722, 'right_ankle': 0.7220073543654681, 'left_hip_yaw': -0.04884422372178685, 'left_hip_roll': -1.671207278970772, 'left_hip_pitch': -0.20681199620773083, 'left_knee': -3.4874657863495715, 'left_ankle': 0.7193570862783006, 'neck_pitch': 1.0285008796940607, 'head_pitch': -1.0097989192713934, 'head_yaw': -2.9719762349128724}
{10: 5.22250246321229, 11: 96.30439335916344, 12: -23.36033812988768, 13: 0.7045307018888589, 14: -41.36797418254776, 20: 2.7985678728511645, 21: 95.7531237765676, 22: 11.849454535378563, 23: 199.8170707541033, 24: -41.21612500657485, 30: -58.92875963196211, 31: 57.85721623112257, 32: 170.2816950736885}
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01 -4.10000000e-02
 -1.66900000e+00 -2.11000000e-01 -3.08200000e+00  7.10000000e-01
  9.48000000e-01 -7.50000000e-01 -2.96400000e+00  0.00000000e+00
  0.00000000e+00 -1.03000000e-01 -1.69800000e+00  3.77000000e-01
 -7.10000000e-02  7.16000000e-01  2.39808239e-02 -0.00000000e+00
 -2.39808239e-02 -2.39808239e-02  4.79616478e-02 -2.39808239e-02
 -0.00000000e+00 -1.67865767e-01  0.00000000e+00  0.00000000e+00
 -0.00000000e+00 -2.39808239e-02 -2.39808239e-02 -2.39808239e-02
 -2.39808239e-02 -7.59908259e-02 -1.17470317e-01  2.12625533e-01
 -1.30964190e-01  3.88617143e-02 -2.96966195e-01 -3.35265994e-01
  1.68023765e-01 -1.73488259e-01 -1.76139757e-01 -9.23215598e-02
 -1.17555737e-01 -1.85262471e-01 -2.09365904e-01 -2.12482750e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
Action: {'right_hip_yaw': -0.08871408956549977, 'right_hip_roll': -1.6851003747256372, 'right_hip_pitch': 0.40715907593899026, 'right_knee': -0.011660532980044547, 'right_ankle': 0.7247580342160465, 'left_hip_yaw': -0.05068440537051808, 'left_hip_roll': -1.6726342886725007, 'left_hip_pitch': -0.20862679372836834, 'left_knee': -3.490280347478188, 'left_ankle': 0.7202076669109873, 'neck_pitch': 1.02608355372055, 'head_pitch': -1.0101273408641058, 'head_yaw': -2.9714852714538575}
{10: 5.082942915448712, 11: 96.54913952769252, 12: -23.32849664175073, 13: 0.6680993266296571, 14: -41.52557652877757, 20: 2.9040025148608897, 21: 95.83488540980089, 22: 11.953434773981899, 23: 199.9783332279546, 24: -41.26485968696336, 30: -58.79025705597259, 31: 57.87603340228596, 32: 170.2535649395918}
[0 0 0]
Observation: [-2.44177896e-04  6.10336575e-04 -9.99999784e-01 -3.90000000e-02
 -1.66900000e+00 -2.11000000e-01 -3.08000000e+00  7.11000000e-01
  9.48000000e-01 -7.50000000e-01 -2.97600000e+00  0.00000000e+00
  0.00000000e+00 -1.03000000e-01 -1.69800000e+00  3.77000000e-01
 -7.10000000e-02  7.16000000e-01 -0.00000000e+00 -2.39808239e-02
 -0.00000000e+00 -2.39808239e-02 -2.39808239e-02 -2.39808239e-02
 -0.00000000e+00  9.59232957e-02  0.00000000e+00  0.00000000e+00
 -0.00000000e+00 -2.39808239e-02 -2.39808239e-02 -2.39808239e-02
 -0.00000000e+00 -7.78310075e-02 -1.18897326e-01  2.10810736e-01
 -1.33778751e-01  3.97122949e-02 -2.99383521e-01 -3.35594416e-01
  1.68514729e-01 -1.69283330e-01 -1.75571695e-01 -8.98857862e-02
 -1.21827364e-01 -1.85818210e-01 -2.08730057e-01 -2.09732071e-01
  0.00000000e+00  0.00000000e+00  0.00000000e+00]
obs shape: (51,)
```

