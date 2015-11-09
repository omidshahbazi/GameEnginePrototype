// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Windows.Forms;
using IE.Docking;
using ManagedWrapper;

namespace IE
{
	partial class MainWindow : Form
	{
		Camera camera;
		Renderer ren0;

		public MainWindow()
		{
			InitializeComponent();

			if (Program.IsRunning)
			{
				Application.Idle += Render;

				new ConsoleWindow().Show(dockPanel, DockState.DockBottomAutoHide);
				new PropertyWindow().Show(dockPanel, DockState.DockRight);

				Program.Core.Initialize();
			}

			if (Program.IsRunning)
			{
				Composite blur = CompositeResourcesManager.Instance.GetComposite("GaussianBlur.composite");

				Scene scene = Program.Core.CreateScene(Name);
				GameObject obj = scene.CreateGameObject("Camera");
				camera = obj.AddComponent<Camera>();
				obj.Transform.WorldPosition = new Vector3(0, 0, 10);

				camera.Type = Camera.ProjectionType.Perspective;
				camera.NearClipDistance = 1.0F;
				camera.FarClipDistance = 1000.0F;
				camera.AddComposite(blur);

				Material mat = MaterialResourcesManager.Instance.GetMaterial("Test.material");
				Mesh mesh = MeshResourcesManager.Instance.GetMesh(Mesh.BasicShapes.Cube);

                //RenderTarget rt = TextureResourcesManager.Instance.CreateRenderTarget("rt0", Vector2.One * 100, Colour.Format.R32F);
                //rt.Camera = camera;

                //Pass pass1 = mat[0];
                //pass1.SetTextureStage(0, rt);

				//obj = scene.CreateGameObject("obj0");
				//Renderer ren = ren = obj.AddComponent<Renderer>();
				//ren.Material = mat;
				//ren.Mesh = mesh;
				//obj.AddComponent("Test");

				GameObject obj0 = null;
				for (float i = 0; i < 100; i++)
				{
					obj0 = scene.CreateGameObject("obj0", obj0);
					ren0 = obj0.AddComponent<Renderer>();
					ren0.Material = mat;
					ren0.Mesh = mesh;
					obj0.AddComponent("Test");
					obj0.Transform.WorldPosition = new Vector3(0.05F * i, 0.05F * i, 0);
                }

				GameObject.Destroy(obj0);

                PropertyWindow.SelectedObject = obj;
			}
		}

		private void Render(object sender, EventArgs e)
		{
			Program.Core.UpdateOneFrame();

			Invalidate();

            Text = Program.Core.FrameStats.FPS + " - " + Program.Core.FrameStats.AverageFrameTime;
		}

		private void sceneWindowToolStripMenuItem_Click(object sender, EventArgs e)
		{
			SceneViewWindow svw = new SceneViewWindow();
			svw.Camera = camera;
			svw.Show(dockPanel, DockState.Document);
		}
	}
}
