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
	public partial class AddVolumeTab : UserControl
	{
		public AddVolumeTab()
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
		public string HeaderFile { get { return headerFile.Text; } }
		public string MetaFile { get { return metaFile.Text; } }
		public string RegFile { get { return regFile.Text; } }

		AddComponentCommandWindow m_Parent;
		
		bool m_HeaderFileDefault = true;
		bool m_MetaFileDefault = true;
		bool m_RegFileDefault = true;

		bool m_CheckDefault = true;

		private void onKeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				m_Parent.Type = AddComponentCommandType.Volume;
				m_Parent.DialogResult = DialogResult.OK;
				m_Parent.Close();
			}
		}

		private void componentName_TextChanged(object sender, EventArgs e)
		{
			m_CheckDefault = false;

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

		private void okay_Click(object sender, EventArgs e)
		{
			m_Parent.Type = AddComponentCommandType.Volume;
			m_Parent.DialogResult = DialogResult.OK;
			m_Parent.Close();
		}

		private void cancel_Click(object sender, EventArgs e)
		{
			m_Parent.Type = AddComponentCommandType.Volume;
			m_Parent.DialogResult = DialogResult.Cancel;
			m_Parent.Close();
		}
	}
}
