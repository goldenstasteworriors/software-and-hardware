### BDX

看一下什么硬件能部署模型

查看占用6006端口的进程lsof -i:6006

更换GPU：export CUDA_VISIBLE_DEVICES=2

批量关闭端口进程：for port in $(seq 6006 6025); do pid=$(lsof -t -i:${port}); if [ -n "$pid" ]; then kill -9 $pid && echo "Killed process on port $port (PID: $pid)"; fi; done

获取跑在GPU0上的含awd的进程：`ps aux | grep awd | grep -f <(nvidia-smi pmon -c 1 | grep ' 0 ' | awk '{print $2}')`

获取存储情况`du -h --max-depth=1 | sort -h`



ljzzy@beibei

dhy



tensorboard --logdir /home/yekangjie/Downloads/AWD-main/output/Duckling_19-22-11-23 --port 6007

2885626:4e-6 早

2885916:1e-5 晚



使用vscode上不了服务器而其他方法能上可以：`rm -rf ~/.vscode-server`



























import torch
print(torch.cuda.is_available())  # 应该返回 True
print(torch.cuda.device_count())  # 应该返回 GPU 的数量



==19-22-08-46 my_bdx_backward/4e-6==

19/22:11 mini_bdx/4e-7



nohup python awd/run.py --task  DucklingCommand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_command_2.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6.yaml  --motion_file awd/data/motions/mini_bdx_all_60fps --headless > log/10900_2.log 2>&1 &







/home/yekangjie/Downloads/garbage/yolov5-autodl/classify/yolov5x-cls.pt











nohup python awd/run.py --resume 1 --task DucklingCommand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_command_2.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6.yaml --motion_file awd/data/motions/mini_bdx_all_60fps --checkpoint /home/yekangjie/Downloads/AWD-main/output/10900.pth --headless > log/10900_2.log 2>&1 &



==stand==

python awd/run.py  --task DucklingStand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_stand.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps  --headless



nohup python awd/run.py  --task DucklingStand --num_envs 256 --cfg_env awd/data/cfg/mini_bdx/duckling_stand_3_s1_L2.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6_no_style.yaml --motion_file awd/data/motions/mini_bdx_all_60fps          --output_path output/stand_3_s1_L2  --headless > log/stand_3_s1_L2.log 2>&1 &



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



python awd/run.py --test --task DucklingCommand --num_envs 128 --cfg_env awd/data/cfg/mini_bdx/duckling_command.yaml --cfg_train awd/data/cfg/mini_bdx/train/amp_duckling_task_4e-6.yaml --motion_file awd/data/motions/mini_bdx_all_60fps/ --checkpoint output/Duckling_21-23-48-56/nn/Duckling_00010900.pth --headless



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



### rewards

1. duckling_poststep中调用具体任务里的`_compute_reward`函数









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
