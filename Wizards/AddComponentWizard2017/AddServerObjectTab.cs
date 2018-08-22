﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AddComponentWizard2017
{
	public partial class AddServerObjectTab : UserControl
	{
		public AddServerObjectTab()
		{
			InitializeComponent();
		}

		public void SetInitialPath(AddComponentCommandWindow parent, string path)
		{
			m_Parent = parent;
			createPath.Text = path;
			componentName.KeyDown += onKeyDown;
		}

		public string ComponentName { get { return componentName.Text; } }
		public string BasePath { get { return createPath.Text; } }
		public string SourceFile { get { return sourceFile.Text; } }
		public string HeaderFile { get { return headerFile.Text; } }
		public string MetaFile { get { return metaFile.Text; } }
		public string RegFile { get { return regFile.Text; } }
		public string InitDataClass { get { return initDataName.Text; } }
		public string EntityLink { get { return entityLink.Text; } }
		public bool CreateInitData { get { return createInitData.Checked; } }
		public bool IncludePositionData { get { return includePosition.Checked; } }

		AddComponentCommandWindow m_Parent;

		bool m_SourceFileDefault = true;
		bool m_HeaderFileDefault = true;
		bool m_MetaFileDefault = true;
		bool m_RegFileDefault = true;
		bool m_InitDataDefault = true;

		bool m_CheckDefault = true;

		private void onKeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				m_Parent.Type = AddComponentCommandType.ServerObject;
				m_Parent.DialogResult = DialogResult.OK;
				m_Parent.Close();
			}
		}

		private void componentName_TextChanged(object sender, EventArgs e)
		{
			m_CheckDefault = false;
			if (m_SourceFileDefault)
			{
				sourceFile.Text = componentName.Text + ".refl.cpp";
			}

			if (m_HeaderFileDefault)
			{
				headerFile.Text = componentName.Text + ".refl.h";
			}

			if (m_MetaFileDefault)
			{
				metaFile.Text = componentName.Text + ".refl.meta.h";
			}

			if (m_RegFileDefault)
			{
				regFile.Text = componentName.Text + ".refl.reg.cpp";
			}

			if (m_InitDataDefault)
			{
				initDataName.Text = componentName.Text + "InitData";
			}

			m_CheckDefault = true;
		}

		private void headerFile_TextChanged(object sender, EventArgs e)
		{
			if (m_CheckDefault == false)
			{
				return;
			}

			m_HeaderFileDefault = false;
		}

		private void sourceFile_TextChanged(object sender, EventArgs e)
		{
			if (m_CheckDefault == false)
			{
				return;
			}

			m_SourceFileDefault = false;
		}

		private void metaFile_TextChanged(object sender, EventArgs e)
		{
			if (m_CheckDefault == false)
			{
				return;
			}

			m_MetaFileDefault = false;
		}

		private void regFile_TextChanged(object sender, EventArgs e)
		{
			if (m_CheckDefault == false)
			{
				return;
			}

			m_RegFileDefault = false;
		}

		private void initDataName_TextChanged(object sender, EventArgs e)
		{
			if (m_CheckDefault == false)
			{
				return;
			}

			m_InitDataDefault = false;
		}

		private void createInitData_CheckedChanged(object sender, EventArgs e)
		{
			initDataName.Enabled = createInitData.Checked;
		}

		private void okay_Click(object sender, EventArgs e)
		{
			m_Parent.Type = AddComponentCommandType.ServerObject;
			m_Parent.DialogResult = DialogResult.OK;
			m_Parent.Close();
		}

		private void cancel_Click(object sender, EventArgs e)
		{
			m_Parent.Type = AddComponentCommandType.ServerObject;
			m_Parent.DialogResult = DialogResult.Cancel;
			m_Parent.Close();
		}
	}
}